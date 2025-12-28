#include <stdint.h>
#include <stdlib.h>
#include "vm_metaspace.h"

VmMetaspace* createVmMetaspace(int16_t dataTypes) {
    VmMetaspace *metaspace = calloc(1, sizeof(VmMetaspace));
    metaspace->dataTypes = dataTypes;
    metaspace->types = calloc(dataTypes, sizeof(VmDataType *));

    return metaspace;
}

VmDataType *createVmDataType(int16_t fieldsCount) {
    VmDataType *dataType = calloc(1, sizeof(VmDataType));
    dataType->fieldsCount = fieldsCount;
    dataType->fields = calloc(fieldsCount, sizeof(VmDataTypeField *));

    return dataType;
}

VmDataTypeField *createVmDataTypeField(VmValueType type, char *name) {
    VmDataTypeField *typeField = calloc(1, sizeof(VmDataTypeField));
    typeField->type = type;
    typeField->name = name;

    return typeField;
}

void destroyVmMetaspace(VmMetaspace* metaspace) {
    if (metaspace == NULL) {
        return;
    }

    for (int i = 0; i < metaspace->dataTypes; ++i) {
        VmDataType *dataType = metaspace->types[i];

        for (int j = 0; j < dataType->fieldsCount; ++j) {
            free(dataType->fields[j]);
        }

        free(dataType);
    }

    free(metaspace);
}

int32_t getVmDataTypeSize(VmDataType *type) {
    if (type == NULL) {
        return 0;
    }
    int32_t size = 0;

    for (int i = 0; i < type->fieldsCount; ++i) {
        size += getVmDataTypeFieldSize(type->fields[i]);
    }

    return size;
}

int32_t getVmDataTypeFieldSize(VmDataTypeField *field) {
    switch (field->type) {
        case TYPE_I8:
            return 1;
        case TYPE_I16:
            return 2;
        case TYPE_I32:
        case TYPE_OBJECT:
            return 4;
    }
}
