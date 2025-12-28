#include <stdint.h>
#include <stddef.h>

typedef enum {
    TYPE_I8,
    TYPE_I16,
    TYPE_I32,
    TYPE_OBJECT,
} VmValueType;

typedef struct VirtualMachineMetaspaceField {
    VmValueType type;
    char* name;
    union {
        int8_t i8;
        int16_t i16;
        int32_t i32;
        void* object;
    };
} VmDataTypeField;

typedef struct VirtualMachineDataType {
    int16_t fieldsCount;

    VmDataTypeField** fields;
} VmDataType;

typedef struct VirtualMachineMetaspace {
    int16_t dataTypes;

    VmDataType** types;
} VmMetaspace;

VmMetaspace* createVmMetaspace(int16_t dataTypes);

VmDataType *createVmDataType(int16_t fieldsCount);

VmDataTypeField *createVmDataTypeField(VmValueType type, char *name);

int32_t getVmDataTypeSize(VmDataType *type);

int32_t getVmDataTypeFieldSize(VmDataTypeField *field);

void destroyVmMetaspace(VmMetaspace* metaspace);
