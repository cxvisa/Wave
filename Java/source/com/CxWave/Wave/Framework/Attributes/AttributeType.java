/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Attributes;

import com.CxWave.Wave.Framework.Type.WaveResourceId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Resources.ResourceEnums.AttributeTypeString;

public class AttributeType
{
    public static AttributeType s_AttributeTypeUI32                   = new AttributeType (1, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI32.getResourceId ());
    public static AttributeType s_AttributeTypeWaveMessageType        = new AttributeType (1, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_WAVE_MESSAGE_TYPE.getResourceId ());
    public static AttributeType s_AttributeTypeWaveMessagePriority    = new AttributeType (1, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_WAVE_MESSAGE_PRIORITY.getResourceId ());
    public static AttributeType s_AttributeTypeWaveServiceId          = new AttributeType (1, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_WAVE_SERVICE_ID.getResourceId ());
    public static AttributeType s_AttributeTypeSerializableObjectType = new AttributeType (1, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SERIALIZABLE_OBJECT_TYPE.getResourceId ());
    public static AttributeType s_AttributeTypeLocationId             = new AttributeType (1, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_LOCATIONID.getResourceId ());
    public static AttributeType s_AttributeTypeUI32Vector             = new AttributeType (2, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI32_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeUI64                   = new AttributeType (3, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI64.getResourceId ());
    public static AttributeType s_AttributeTypeUI64Vector             = new AttributeType (4, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI64_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeSI64                   = new AttributeType (5, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI64.getResourceId ());
    public static AttributeType s_AttributeTypeSI64Vector             = new AttributeType (6, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI64_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeSI32                   = new AttributeType (7, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI32.getResourceId ());
    public static AttributeType s_AttributeTypeSI32Vector             = new AttributeType (8, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI32_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeUI16                   = new AttributeType (9, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI16.getResourceId ());
    public static AttributeType s_AttributeTypeUI16Vector             = new AttributeType (10, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI16_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeSI16                   = new AttributeType (11, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI16.getResourceId ());
    public static AttributeType s_AttributeTypeSI16Vector             = new AttributeType (12, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI16_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeUI8                    = new AttributeType (13, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI8.getResourceId ());
    public static AttributeType s_AttributeTypeUI8Vector              = new AttributeType (14, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI8_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeSI8                    = new AttributeType (15, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI8.getResourceId ());
    public static AttributeType s_AttributeTypeSI8Vector              = new AttributeType (16, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SI8_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeObjectId               = new AttributeType (17, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_OBJECTID.getResourceId ());
    public static AttributeType s_AttributeTypeObjectIdVector         = new AttributeType (18, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_OBJECTID_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeComposition            = new AttributeType (19, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_COMPOSITION.getResourceId ());
    public static AttributeType s_AttributeTypeCompositionVector      = new AttributeType (20, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_COMPOSITION_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeBool                   = new AttributeType (21, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_BOOL.getResourceId ());
    public static AttributeType s_AttributeTypeBoolVector             = new AttributeType (22, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_BOOL_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeChar                   = new AttributeType (23, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_CHAR.getResourceId ());
    public static AttributeType s_AttributeTypeString                 = new AttributeType (24, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_STRING.getResourceId ());
    public static AttributeType s_AttributeTypeStringVector           = new AttributeType (25, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_STRING_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeWorldWideName          = new AttributeType (26, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_WORLD_WIDE_NAME.getResourceId ());
    public static AttributeType s_AttributeTypeWorldWideNameVector    = new AttributeType (27, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_WORLD_WIDE_NAME_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeMacAddress             = new AttributeType (28, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_MACADDRESS.getResourceId ());
    public static AttributeType s_AttributeTypeMacAddressVector       = new AttributeType (29, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_MACADDRESS_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeIpV4Address            = new AttributeType (30, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPV4ADDRESS.getResourceId ());
    public static AttributeType s_AttributeTypeIpV4AddressVector      = new AttributeType (31, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPV4ADDRESS_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeIpV6Address            = new AttributeType (32, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPV6ADDRESS.getResourceId ());
    public static AttributeType s_AttributeTypeIpV6AddressVector      = new AttributeType (33, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPV6ADDRESS_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeEnum                   = new AttributeType (34, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_ENUM.getResourceId ());
    public static AttributeType s_AttributeTypeDate                   = new AttributeType (35, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_DATE.getResourceId ());
    public static AttributeType s_AttributeTypeDateVector             = new AttributeType (36, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_DATE_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeTime                   = new AttributeType (37, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_TIME.getResourceId ());
    public static AttributeType s_AttributeTypeTimeVector             = new AttributeType (38, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_TIME_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeDateTime               = new AttributeType (39, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_DATETIME.getResourceId ());
    public static AttributeType s_AttributeTypeDateTimeVector         = new AttributeType (40, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_DATETIME_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeBitMap                 = new AttributeType (41, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_BITMAP.getResourceId ());
    public static AttributeType s_AttributeTypeDecimal64              = new AttributeType (42, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_DECIMAL64.getResourceId ());
    public static AttributeType s_AttributeTypeDecimal64Vector        = new AttributeType (43, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_DECIMAL64_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeUnion                  = new AttributeType (44, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UNION.getResourceId ());
    public static AttributeType s_AttributeTypeIpV4AddressNetworkMask = new AttributeType (45, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPV4ADDRESS_NETWORK_MASK.getResourceId ());
    public static AttributeType s_AttributeTypeIpV6AddressNetworkMask = new AttributeType (46, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPV6ADDRESS_NETWORK_MASK.getResourceId ());
    public static AttributeType s_AttributeTypeSnmpObjectId           = new AttributeType (47, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SNMPOBJECTID.getResourceId ());
    public static AttributeType s_AttributeTypeUI32Range              = new AttributeType (48, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI32_RANGE.getResourceId ());
    public static AttributeType s_AttributeTypeIpVxAddress            = new AttributeType (49, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPVXADDRESS.getResourceId ());
    public static AttributeType s_AttributeTypeIpVxAddressVector      = new AttributeType (50, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPVXADDRESS_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeLargeObject            = new AttributeType (51, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_LARGEOBJECT.getResourceId ());
    public static AttributeType s_AttributeTypeMACRange               = new AttributeType (52, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_MAC_RANGE.getResourceId ());
    public static AttributeType s_AttributeTypeUI32UC                 = new AttributeType (53, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI32_UC.getResourceId ());
    public static AttributeType s_AttributeTypeStringUC               = new AttributeType (54, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_STRING_UC.getResourceId ());
    public static AttributeType s_AttributeTypeBoolUC                 = new AttributeType (55, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_BOOL_UC.getResourceId ());
    public static AttributeType s_AttributeTypeEnumUC                 = new AttributeType (56, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_ENUM_UC.getResourceId ());
    public static AttributeType s_AttributeTypeMacAddress2            = new AttributeType (57, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_MACADDRESS2.getResourceId ());
    public static AttributeType s_AttributeTypeMacAddress2Vector      = new AttributeType (58, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_MACADDRESS2_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeResourceId             = new AttributeType (59, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_RESOURCEID.getResourceId ());
    public static AttributeType s_AttributeTypeResourceEnum           = new AttributeType (59, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_RESOURCEENUM.getResourceId ());
    public static AttributeType s_AttributeTypeResourceIdVector       = new AttributeType (60, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_RESOURCEID_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeResourceEnumVector     = new AttributeType (60, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_RESOURCEENUM_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeIpV4AddressUC          = new AttributeType (61, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_IPV4ADDRESS_UC.getResourceId ());
    public static AttributeType s_AttributeTypeUI32VectorUC           = new AttributeType (62, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI32_VECTOR_UC.getResourceId ());
    public static AttributeType s_AttributeTypeStringVectorUC         = new AttributeType (63, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_STRING_UC.getResourceId ());
    public static AttributeType s_AttributeTypeHostUC                 = new AttributeType (64, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_HOST_UC.getResourceId ());
    public static AttributeType s_AttributeTypeUI64UC                 = new AttributeType (65, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UI64_UC.getResourceId ());
    public static AttributeType s_AttributeTypeSqlBetween             = new AttributeType (66, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SQL_BETWEEN.getResourceId ());
    public static AttributeType s_AttributeTypeSqlIn                  = new AttributeType (67, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SQL_IN.getResourceId ());
    public static AttributeType s_AttributeTypeStringVectorVector     = new AttributeType (68, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_STRING_VECTOR_VECTOR.getResourceId ());
    public static AttributeType s_AttributeTypeSerializableObject     = new AttributeType (69, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SERIALIZABLE_OBJECT.getResourceId ());
    public static AttributeType s_AttributeTypeUUID                   = new AttributeType (70, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_UUID.getResourceId ());
    public static AttributeType s_AttributeTypeSqlExists              = new AttributeType (71, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_SQL_EXISTS.getResourceId ());
    public static AttributeType s_AttributeTypeUri                    = new AttributeType (72, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_URI.getResourceId ());
    public static AttributeType s_AttributeTypeNumber                 = new AttributeType (73, AttributeTypeString.WAVE_ATTRIBUTE_TYPE_NUMBER.getResourceId ());

    private UI32       m_attributeTypeIndictor;
    private WaveResourceId m_attributeTypeResourceId;

    public AttributeType (final UI32 attributeTypeIndicator, final WaveResourceId attributeTypeResourceId)
    {
        m_attributeTypeIndictor = attributeTypeIndicator;
        m_attributeTypeResourceId = attributeTypeResourceId;
    }

    public AttributeType (final int attributeTypeIndicator, final WaveResourceId attributeTypeResourceId)
    {
        m_attributeTypeIndictor = new UI32 (attributeTypeIndicator);
        m_attributeTypeResourceId = attributeTypeResourceId;
    }

    public UI32 getAttributeTypeIndictor ()
    {
        return m_attributeTypeIndictor;
    }

    public void setAttributeTypeIndictor (final UI32 attributeTypeIndictor)
    {
        m_attributeTypeIndictor = attributeTypeIndictor;
    }

    public WaveResourceId getAttributeTypeResourceId ()
    {
        return m_attributeTypeResourceId;
    }

    public void setAttributeTypeResourceId (final WaveResourceId attributeTypeResourceId)
    {
        m_attributeTypeResourceId = attributeTypeResourceId;
    }

}
