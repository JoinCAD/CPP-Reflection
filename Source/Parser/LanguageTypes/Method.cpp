/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Method.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "LanguageTypes/Class.h"
#include "LanguageTypes/Method.h"

#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>

Method::Method(
    const Cursor &cursor, 
    const Namespace &currentNamespace, 
    Class *parent
)
    : LanguageType( cursor, currentNamespace )
    , Invokable( cursor )
    , m_isConst( cursor.IsConst( ) )
    , m_parent( parent )
    , m_name( cursor.GetSpelling( ) )
{
	//if return type is a typeDef, which definition is inside class scope, we have to add a class name before typeDef name
	fixReturnType();
}

bool Method::ShouldCompile(void) const
{
    return isAccessible( );
}

TemplateData Method::CompileTemplate(const ReflectionParser *context) const
{
    TemplateData data { TemplateData::Type::Object };

    data[ "name" ] = m_name;
        
    data[ "parentQualifiedName" ] = m_parent->m_qualifiedName;

    data[ "qualifiedSignature" ] = getQualifiedSignature( );

    m_metaData.CompileTemplateData( data, context );

    return data;
}

bool Method::isAccessible(void) const
{
    if (m_accessModifier != CX_CXXPublic)
        return false;

    // if the parent wants white listed method, then we must have 
    // the enable flag
    if (m_parent->GetMetaData( ).GetFlag( native_property::WhiteListMethods ))
        return m_metaData.GetFlag( native_property::Enable );


    //remove operators from meta data, otherwise it can cause compile errors
    std::string prefix = "operator";    
    bool isOperator = strncmp(m_name.c_str(), prefix.c_str(), prefix.size()) == 0;

    //next condition is optional:
    //parse only methods that don't take arguments
    bool takesArguments = m_signature.size() > 0;

    // must not be explicitly disabled
    return !m_metaData.GetFlag(native_property::Disable) && !takesArguments && !isOperator;
}

std::string Method::getQualifiedSignature(void) const
{
    auto argsList = boost::join( m_signature, ", " );

    std::string constNess = m_isConst ? " const" : "";

    return (boost::format( "%1%(%2%::*)(%3%)%4%" ) % 
        m_returnType % 
        m_parent->m_qualifiedName % 
        argsList % constNess
    ).str( );
}

void Method::fixReturnType()
{
	if (m_parent->m_typeDefs.size() <= 0)
		return;

	for (auto typeDef : m_parent->m_typeDefs)
	{
		auto index = m_returnType.find(*typeDef, 0);
		if (index != std::string::npos)
		{
			std::string parentName = m_parent->m_displayName + "::";
			m_returnType.insert(index, parentName);
		}
	}
}
