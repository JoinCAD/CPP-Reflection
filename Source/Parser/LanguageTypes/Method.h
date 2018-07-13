/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Method.h
** --------------------------------------------------------------------------*/

#pragma once

#include "LanguageType.h"
#include "Invokable.h"

class Class;

typedef std::unordered_map<std::string, std::string> string_map;
class Method 
    : public LanguageType
    , public Invokable
{
public:
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
	static string_map undefined_teigha_types;
	void fixReturnType(Cursor);
};