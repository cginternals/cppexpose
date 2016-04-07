
import os
import sys
import shutil

directory = os.path.join(sys.argv[1], 'propertyInstanciationTests')
generatedCppsFile = sys.argv[2]

# 
datatypes = ['bool', 'float', 'double', 'int8_t', 'uint8_t', 'int16_t', 'uint16_t', 'int32_t', 'uint32_t', 'int64_t', 'uint64_t', 'string', 'Variant']


def getPropertyTestFileContent(datatype, datatypeC):
    content = '''
#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstance${CAPITALDATATYPE}_test : public testing::Test
{
public:
    PropertyInstance${CAPITALDATATYPE}_test()
    {
    }

protected:
};

namespace {
${DATATYPE} staticGetter()
{
    return ${DATATYPE}();
}

void staticSetter(${DATATYPE} /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return ${DATATYPE}();};
    auto set = [] (const ${DATATYPE} & /*val*/) {};

    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", get, set);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::constgetterconst, &MyObject<${DATATYPE}>::setterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setter);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return ${DATATYPE}();};

    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", get);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", &staticGetter);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::constgetterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::getterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<${DATATYPE}>();
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<${DATATYPE}>(${DATATYPE}());
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return ${DATATYPE}();};
    auto set = [] (const ${DATATYPE} & /*val*/) {};
    auto accessor = new AccessorGetSet<${DATATYPE}>(get, set);

    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new AccessorGetSet<${DATATYPE}>(&staticGetter, &staticSetter);

    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<${DATATYPE}>(obj, &MyObject<${DATATYPE}>::constgetterconst, &MyObject<${DATATYPE}>::setterconst);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<${DATATYPE}>(obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setterconst);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<${DATATYPE}>(obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setter);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const ${DATATYPE}>();
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const ${DATATYPE}>(${DATATYPE}());
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] () {return ${DATATYPE}();};
    auto accessor = new AccessorGetSet<const ${DATATYPE}>(get);

    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new AccessorGetSet<const ${DATATYPE}>(&staticGetter);

    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<const ${DATATYPE}>(obj, &MyObject<${DATATYPE}>::constgetterconst);
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<const ${DATATYPE}>(obj, &MyObject<${DATATYPE}>::getterconst);
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}
'''
    content = content.replace('${DATATYPE}', datatype)
    content = content.replace('${CAPITALDATATYPE}', datatypeC)
    return content

def getPropertyArrayTestFileContent(datatype, datatypeC):
    content = '''

#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstance${CAPITALDATATYPE}Array_test : public testing::Test
{
public:
    PropertyInstance${CAPITALDATATYPE}Array_test()
    {
    }

protected:
};

namespace {
${DATATYPE} staticGetter(size_t)
{
    return ${DATATYPE}();
}

void staticSetter(size_t, ${DATATYPE} /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return ${DATATYPE}();};
    auto set = [] (size_t, const ${DATATYPE} & /*val*/) {};

    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", get, set);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::arrayConstgetterconst, &MyObject<${DATATYPE}>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::arrayGetterconst, &MyObject<${DATATYPE}>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::arrayGetterconst, &MyObject<${DATATYPE}>::arraySetter);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return ${DATATYPE}();};

    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", get);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", &staticGetter);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::arrayConstgetterconst);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::arrayGetterconst);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<${DATATYPE}, 1>();
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<${DATATYPE}, 1>(std::array<${DATATYPE}, 1>());
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return ${DATATYPE}();};
    auto set = [] (size_t, const ${DATATYPE} & /*val*/) {};
    auto accessor = new ArrayAccessorGetSet<${DATATYPE}, 1>(get, set);

    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new ArrayAccessorGetSet<${DATATYPE}, 1>(&staticGetter, &staticSetter);

    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new ArrayAccessorGetSet<${DATATYPE}, 1>(obj, &MyObject<${DATATYPE}>::arrayConstgetterconst, &MyObject<${DATATYPE}>::arraySetterconst);
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new ArrayAccessorGetSet<${DATATYPE}, 1>(obj, &MyObject<${DATATYPE}>::arrayGetterconst, &MyObject<${DATATYPE}>::arraySetterconst);
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new ArrayAccessorGetSet<${DATATYPE}, 1>(obj, &MyObject<${DATATYPE}>::arrayGetterconst, &MyObject<${DATATYPE}>::arraySetter);
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<const ${DATATYPE}, 1>();
    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<const ${DATATYPE}, 1>(std::array<${DATATYPE}, 1>());
    auto prop = new PropertyArray<${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return ${DATATYPE}();};
    auto accessor = new ArrayAccessorGetSet<const ${DATATYPE}, 1>(get);

    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new ArrayAccessorGetSet<const ${DATATYPE}, 1>(&staticGetter);

    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new ArrayAccessorGetSet<const ${DATATYPE}, 1>(obj, &MyObject<${DATATYPE}>::arrayConstgetterconst);
    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}Array_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new ArrayAccessorGetSet<const ${DATATYPE}, 1>(obj, &MyObject<${DATATYPE}>::arrayGetterconst);
    auto prop = new PropertyArray<const ${DATATYPE}, 1>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(std::array<${DATATYPE}, 1>), prop->type());


    delete prop;
    delete obj;
}

'''
    content = content.replace('${DATATYPE}', datatype)
    content = content.replace('${CAPITALDATATYPE}', datatypeC)
    return content

def generatePropertyInstanciationTest(filepath, datatype, datatypeC):
    content = getPropertyTestFileContent(datatype, datatypeC)
    with open(filepath, 'wb') as f:
        f.write(content)

def generatePropertyArrayInstanciationTest(filepath, datatype, datatypeC):
    content = getPropertyArrayTestFileContent(datatype, datatypeC)
    with open(filepath, 'wb') as f:
        f.write(content)

print 'Generating reflectionzeug property instanciation tests.'

if os.path.exists(directory):
    shutil.rmtree(directory)
os.mkdir(directory)

with open(generatedCppsFile, 'wb') as f:
    for datatype in datatypes:
        datatypeC = datatype.title()
        filepath = os.path.join(directory, 'PropertyInstanciation' + datatypeC + '_test.cpp')
        generatePropertyInstanciationTest(filepath, datatype, datatypeC)
        filename = '/'.join(filepath.split('/')[-2:])
        f.write(filename)
        f.write("\n")
    for datatype in datatypes:
        datatypeC = datatype.title()
        filepath = os.path.join(directory, 'PropertyInstanciation' + datatypeC + 'Array_test.cpp')
        generatePropertyArrayInstanciationTest(filepath, datatype, datatypeC)
        filename = '/'.join(filepath.split('/')[-2:])
        f.write(filename)
        f.write("\n")

print 'Generation of reflectionzeug property instanciation tests done!'
