/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Method.h
** --------------------------------------------------------------------------*/

#pragma once

#include "LanguageType.h"
#include "Invokable.h"

class Class;

class Method 
    : public LanguageType
    , public Invokable
{
public:
#ifdef TEIGHA_API_SETTINGS
	static std::vector<std::string> returnTypesToIgnore;
#endif

    Method(
        const Cursor &cursor, 
        const Namespace &currentNamespace, 
        Class *parent = nullptr
    );

    virtual ~Method(void) { }

    bool ShouldCompile(void) const;
    
    TemplateData CompileTemplate(
        const ReflectionParser *context
    ) const override;

private:
    bool m_isConst;

    Class *m_parent;

    std::string m_name;

    bool isAccessible(void) const;

    std::string getQualifiedSignature(void) const;

#if defined TEIGHA_API_SETTINGS
	void fixReturnType(Cursor);
#endif
};