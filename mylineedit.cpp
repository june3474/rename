#include "mylineedit.h"

#include <QToolButton>
#include <QStyle>

/************************************************
 * binary representations of two icons.
 * define static variables outside of the class
 ************************************************/
const uchar MyLineEdit::OK_ICON_DATA[794] = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x03, 0x00, 0x00, 0x00, 0xf3, 0x6a, 0x9c, 0x09, 0x00, 0x00, 0x00,
    0x03, 0x73, 0x42, 0x49, 0x54, 0x08, 0x08, 0x08, 0xdb, 0xe1, 0x4f, 0xe0,
    0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x02, 0x61,
    0x00, 0x00, 0x02, 0x61, 0x01, 0xc1, 0x30, 0x55, 0xfa, 0x00, 0x00, 0x00,
    0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72,
    0x65, 0x00, 0x77, 0x77, 0x77, 0x2e, 0x69, 0x6e, 0x6b, 0x73, 0x63, 0x61,
    0x70, 0x65, 0x2e, 0x6f, 0x72, 0x67, 0x9b, 0xee, 0x3c, 0x1a, 0x00, 0x00,
    0x01, 0x92, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
    0x00, 0x40, 0x00, 0x00, 0x33, 0x00, 0x00, 0x80, 0x00, 0x00, 0x55, 0x00,
    0x00, 0x4d, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x49, 0x00, 0x00, 0x5c, 0x00,
    0x00, 0x5c, 0x00, 0x00, 0x56, 0x00, 0x04, 0x55, 0x04, 0x03, 0x52, 0x03,
    0x03, 0x50, 0x03, 0x05, 0x4d, 0x05, 0x08, 0x52, 0x08, 0x07, 0x4d, 0x07,
    0x06, 0x46, 0x06, 0x06, 0x45, 0x06, 0x24, 0x77, 0x24, 0x06, 0x44, 0x06,
    0x0b, 0x69, 0x0b, 0x13, 0x67, 0x13, 0x12, 0x68, 0x12, 0x10, 0x6b, 0x10,
    0x06, 0x5d, 0x06, 0x07, 0x58, 0x07, 0x0a, 0x55, 0x0a, 0x08, 0x68, 0x08,
    0x09, 0x4b, 0x09, 0x0c, 0x6c, 0x0c, 0x0a, 0x48, 0x0a, 0x0c, 0x44, 0x0b,
    0x11, 0x47, 0x0c, 0x1f, 0x72, 0x1e, 0x0f, 0x79, 0x0d, 0x1f, 0x77, 0x1f,
    0x1d, 0x7a, 0x1d, 0x1b, 0x7b, 0x1a, 0x17, 0x7e, 0x16, 0x12, 0x7e, 0x10,
    0x1e, 0x6d, 0x1e, 0x0b, 0x79, 0x09, 0x50, 0xa0, 0x4e, 0x12, 0x83, 0x10,
    0x36, 0x86, 0x31, 0x3b, 0x8d, 0x31, 0x26, 0x7b, 0x1d, 0x30, 0x58, 0x1d,
    0x32, 0x78, 0x25, 0x37, 0x79, 0x2a, 0x3e, 0x6e, 0x29, 0x42, 0x7a, 0x32,
    0x43, 0x6c, 0x2a, 0x4b, 0x7b, 0x3a, 0x40, 0xab, 0x0d, 0x44, 0xb0, 0x10,
    0x46, 0x6d, 0x2b, 0x49, 0xbc, 0x0f, 0x4a, 0x71, 0x2a, 0x4a, 0xc0, 0x0f,
    0x4b, 0xc0, 0x0f, 0x4e, 0xaf, 0x21, 0x51, 0xb7, 0x21, 0x52, 0xb5, 0x23,
    0x53, 0xd1, 0x11, 0x57, 0xbb, 0x1a, 0x59, 0x9b, 0x39, 0x5d, 0xb1, 0x2d,
    0x5f, 0xb4, 0x44, 0x60, 0x9b, 0x3c, 0x60, 0xa2, 0x44, 0x61, 0xcf, 0x1c,
    0x62, 0xb8, 0x44, 0x63, 0xb4, 0x45, 0x65, 0xa8, 0x49, 0x65, 0xab, 0x4e,
    0x65, 0xb0, 0x53, 0x66, 0x97, 0x39, 0x66, 0x9a, 0x3d, 0x67, 0xb4, 0x53,
    0x67, 0xb5, 0x53, 0x68, 0xad, 0x4d, 0x69, 0xb8, 0x53, 0x6a, 0xb4, 0x2d,
    0x6a, 0xbb, 0x4b, 0x6b, 0xb5, 0x49, 0x6d, 0xb1, 0x62, 0x6e, 0xb4, 0x62,
    0x6f, 0x9d, 0x3b, 0x6f, 0xb5, 0x62, 0x70, 0xb2, 0x59, 0x70, 0xb8, 0x63,
    0x71, 0xb2, 0x56, 0x71, 0xc2, 0x2f, 0x74, 0xbe, 0x57, 0x77, 0xb7, 0x5f,
    0x77, 0xc6, 0x53, 0x78, 0xb8, 0x71, 0x78, 0xd0, 0x30, 0x7a, 0xa8, 0x3e,
    0x7a, 0xbb, 0x72, 0x7a, 0xbe, 0x65, 0x7e, 0xc6, 0x4e, 0x80, 0xc1, 0x74,
    0x81, 0xc4, 0x5a, 0x83, 0xbc, 0x55, 0x83, 0xc0, 0x81, 0x84, 0xbd, 0x56,
    0x85, 0xc2, 0x82, 0x86, 0xc2, 0x68, 0x88, 0xc0, 0x5f, 0x8a, 0xc3, 0x65,
    0x8a, 0xc3, 0x72, 0x8a, 0xc7, 0x83, 0x8b, 0xc4, 0x75, 0x8c, 0xc1, 0x68,
    0x8c, 0xdf, 0x3a, 0x8d, 0xc3, 0x6b, 0x90, 0xc6, 0x57, 0x91, 0xcd, 0x91,
    0x92, 0xc1, 0x73, 0x92, 0xc2, 0x71, 0x92, 0xc4, 0x73, 0x93, 0xc2, 0x76,
    0x94, 0xc5, 0x70, 0x95, 0xd0, 0x91, 0x97, 0xc8, 0x7e, 0x99, 0xc9, 0x7c,
    0x9e, 0xcf, 0x86, 0xa1, 0xcf, 0x86, 0xa4, 0xe0, 0xa2, 0xae, 0xda, 0x96,
    0xcc, 0xcb, 0x5e, 0xd7, 0x00, 0x00, 0x00, 0x38, 0x74, 0x52, 0x4e, 0x53,
    0x00, 0x02, 0x04, 0x05, 0x06, 0x09, 0x0a, 0x0b, 0x0e, 0x24, 0x27, 0x3b,
    0x45, 0x4b, 0x53, 0x5d, 0x63, 0x6e, 0x78, 0x81, 0x81, 0x87, 0x8f, 0x95,
    0x9a, 0xa0, 0xa2, 0xad, 0xb6, 0xbf, 0xc1, 0xc6, 0xcb, 0xd5, 0xd6, 0xdc,
    0xdf, 0xdf, 0xe1, 0xe4, 0xe7, 0xe9, 0xed, 0xee, 0xee, 0xf6, 0xf7, 0xfa,
    0xfb, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 0x7d, 0xe2, 0xe0, 0x59,
    0x00, 0x00, 0x00, 0xb6, 0x49, 0x44, 0x41, 0x54, 0x18, 0xd3, 0x63, 0x60,
    0xa0, 0x1f, 0xe0, 0x50, 0xd1, 0xe1, 0xc2, 0x14, 0x65, 0xd7, 0x6c, 0x6a,
    0xd5, 0xe5, 0x44, 0x17, 0x65, 0xd3, 0x68, 0x68, 0x69, 0x69, 0xd6, 0x86,
    0xf2, 0xc4, 0x44, 0x20, 0x34, 0xab, 0x7a, 0x4d, 0x7d, 0x65, 0x65, 0xa3,
    0x1e, 0x84, 0x27, 0x1f, 0x93, 0x28, 0x09, 0xa2, 0x59, 0xd4, 0xca, 0x8b,
    0xf3, 0x72, 0x6a, 0x0d, 0xb8, 0xc1, 0xa2, 0xb2, 0xbe, 0x25, 0x45, 0xc1,
    0x12, 0x0c, 0x0c, 0xcc, 0xaa, 0x85, 0x99, 0x69, 0xc9, 0x55, 0x46, 0x3c,
    0x10, 0xc5, 0xfa, 0xa5, 0x11, 0xd1, 0xf9, 0x3e, 0xe2, 0x4c, 0xca, 0x05,
    0xe9, 0xb1, 0x91, 0xd5, 0xc6, 0xbc, 0x50, 0x93, 0xa5, 0x5c, 0xe2, 0xfc,
    0x82, 0xb2, 0x3c, 0xb4, 0xb2, 0x13, 0x42, 0x02, 0xeb, 0x4c, 0xf9, 0xe0,
    0xf6, 0x4b, 0xbb, 0x87, 0xbb, 0x79, 0x65, 0x54, 0x24, 0x85, 0x79, 0xe7,
    0x9a, 0xf3, 0x23, 0xb9, 0x4b, 0x26, 0xc0, 0xd5, 0xde, 0xd1, 0xc1, 0xd2,
    0x22, 0xd4, 0x44, 0x00, 0xc5, 0xbd, 0x72, 0xfe, 0xce, 0xd6, 0x76, 0xb6,
    0xf1, 0x66, 0x82, 0x68, 0xfe, 0x50, 0x88, 0xf2, 0x74, 0x4a, 0xb1, 0x12,
    0xc2, 0xf0, 0xb5, 0x52, 0x6a, 0x99, 0x8d, 0x30, 0x66, 0x60, 0x30, 0x2a,
    0x1a, 0x8a, 0xd2, 0x29, 0x36, 0x00, 0x43, 0x30, 0x23, 0xcd, 0x49, 0xc5,
    0xb9, 0x40, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
    0x60, 0x82
  };
const uchar MyLineEdit::ERROR_ICON_DATA[1251] = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x16,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xc4, 0xb4, 0x6c, 0x3b, 0x00, 0x00, 0x00,
    0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0d, 0xd7, 0x00, 0x00, 0x0d,
    0xd7, 0x01, 0x42, 0x28, 0x9b, 0x78, 0x00, 0x00, 0x00, 0x07, 0x74, 0x49,
    0x4d, 0x45, 0x07, 0xd7, 0x0c, 0x1b, 0x16, 0x18, 0x36, 0xd4, 0x0d, 0x69,
    0xaa, 0x00, 0x00, 0x00, 0x06, 0x62, 0x4b, 0x47, 0x44, 0x00, 0xff, 0x00,
    0xff, 0x00, 0xff, 0xa0, 0xbd, 0xa7, 0x93, 0x00, 0x00, 0x04, 0x70, 0x49,
    0x44, 0x41, 0x54, 0x78, 0xda, 0x85, 0xd5, 0x7b, 0x8c, 0x5c, 0x55, 0x1d,
    0x07, 0xf0, 0xcf, 0xbd, 0x77, 0x66, 0x76, 0x67, 0xf6, 0xbd, 0x2d, 0xf6,
    0x45, 0xb7, 0x74, 0xb3, 0xd0, 0x16, 0x6b, 0xbb, 0x16, 0x4b, 0xd2, 0xd8,
    0x60, 0x44, 0x10, 0x6d, 0x68, 0x89, 0x62, 0xe2, 0x23, 0xc4, 0x40, 0xa8,
    0x6c, 0x02, 0xf8, 0x6a, 0x13, 0x83, 0x46, 0x91, 0xbf, 0x7c, 0xc5, 0x98,
    0x10, 0xa3, 0x12, 0x43, 0x8c, 0x7f, 0x00, 0x21, 0x95, 0xd0, 0x90, 0xc2,
    0x1f, 0x90, 0x48, 0x42, 0xb4, 0x0d, 0xb5, 0x01, 0xb1, 0x34, 0x74, 0xdd,
    0xb5, 0x75, 0x2b, 0xdd, 0x87, 0xfb, 0x98, 0xd9, 0xee, 0xee, 0xec, 0xec,
    0xcc, 0xdc, 0xb9, 0xd7, 0x09, 0xe5, 0x2f, 0x1b, 0xca, 0x37, 0xf9, 0x9e,
    0x93, 0xdf, 0xf9, 0xe3, 0x73, 0xce, 0x7f, 0x27, 0xf0, 0x21, 0x79, 0x94,
    0x96, 0x5e, 0xb6, 0x44, 0x6c, 0x44, 0x26, 0x65, 0x36, 0xe6, 0xec, 0x21,
    0x8a, 0xae, 0x92, 0x0f, 0x82, 0x83, 0x9f, 0xb1, 0x23, 0xe2, 0x3b, 0x59,
    0x0e, 0xe4, 0xe8, 0xcd, 0x46, 0x91, 0xb0, 0xd9, 0x7a, 0xad, 0xa6, 0x46,
    0xad, 0xce, 0x89, 0x98, 0xdf, 0xcd, 0xf0, 0xfc, 0x2f, 0x89, 0x3f, 0x14,
    0x3e, 0x4c, 0x61, 0x0d, 0x3f, 0xcd, 0xf1, 0x60, 0x6f, 0x77, 0x77, 0xa6,
    0x7f, 0xdf, 0x3e, 0x6b, 0xf7, 0xee, 0xd5, 0xbe, 0x71, 0x23, 0x61, 0xa8,
    0x36, 0x3f, 0x6f, 0xe6, 0x8d, 0x37, 0x8c, 0x1d, 0x3b, 0x66, 0x72, 0x74,
    0x54, 0x85, 0x13, 0x55, 0xee, 0xfb, 0x21, 0x23, 0x1f, 0x08, 0x1f, 0xa6,
    0x6b, 0x2d, 0x47, 0xdb, 0xf9, 0x74, 0xff, 0xee, 0xdd, 0xb6, 0xdc, 0x7f,
    0xbf, 0x96, 0xce, 0xce, 0x2b, 0x6e, 0x4f, 0x91, 0x24, 0x89, 0x8b, 0xaf,
    0xbc, 0xe2, 0x9d, 0x67, 0x9e, 0x51, 0x8a, 0xe3, 0xd9, 0x2a, 0xfb, 0xbf,
    0xcf, 0xeb, 0x57, 0xc0, 0x9f, 0x23, 0x7b, 0x2b, 0xcf, 0x75, 0x71, 0xa0,
    0x7f, 0x70, 0xd0, 0xc0, 0x3d, 0x5f, 0x13, 0x46, 0x81, 0x20, 0xa0, 0xb9,
    0x4a, 0x13, 0xa4, 0x48, 0xdf, 0xdf, 0xd2, 0x14, 0xcc, 0x9d, 0x3e, 0xed,
    0xcc, 0x53, 0x4f, 0x99, 0x4b, 0xd3, 0xe9, 0x32, 0x7b, 0x7e, 0xc4, 0x79,
    0x88, 0x00, 0xc1, 0xbd, 0x3c, 0xd0, 0xc1, 0xa1, 0x0d, 0x5d, 0x5d, 0xfa,
    0xef, 0x3e, 0xa0, 0x5e, 0xbf, 0xa4, 0x75, 0x60, 0xc0, 0xd2, 0xc5, 0x11,
    0x41, 0x7d, 0x89, 0x5a, 0x59, 0x52, 0x59, 0x12, 0x2f, 0x2d, 0x2a, 0xcf,
    0xce, 0xc9, 0xf6, 0x6d, 0xb2, 0x30, 0x36, 0xa6, 0xb5, 0x50, 0x90, 0x5d,
    0x59, 0xb1, 0x3c, 0x35, 0xd5, 0x56, 0x67, 0x7b, 0x99, 0xa7, 0xdf, 0x25,
    0x8d, 0xe0, 0xcb, 0x74, 0x5e, 0xc7, 0x91, 0xd5, 0x74, 0x6c, 0xbc, 0x69,
    0xa7, 0xb8, 0x2b, 0xd5, 0x71, 0xcb, 0x67, 0x6c, 0xfa, 0xd2, 0xd7, 0x85,
    0xbd, 0xab, 0x8c, 0x1f, 0x7f, 0x51, 0x2e, 0x2c, 0x6b, 0xaa, 0x4a, 0x73,
    0xd3, 0x72, 0x83, 0xbb, 0x5d, 0x7f, 0x70, 0x48, 0x4b, 0x5f, 0x9f, 0x73,
    0x2f, 0xbc, 0xa0, 0xa3, 0xa3, 0xc3, 0xca, 0xb9, 0x73, 0x2a, 0x49, 0xb2,
    0xb9, 0x8f, 0xbf, 0xbd, 0xca, 0x68, 0x88, 0xe0, 0x46, 0xf6, 0xe7, 0x59,
    0xdf, 0x1e, 0x04, 0xf2, 0xd7, 0x64, 0x2c, 0x2c, 0x4c, 0x2a, 0xf4, 0x6f,
    0xa1, 0x39, 0xaf, 0xda, 0x71, 0xb3, 0x8d, 0xf7, 0x7c, 0xdb, 0x85, 0xc9,
    0x31, 0xe3, 0x53, 0xa3, 0x82, 0x8f, 0xed, 0xb2, 0xed, 0xe0, 0x83, 0x82,
    0x30, 0x54, 0xb8, 0x76, 0x83, 0xe5, 0xb4, 0xa1, 0x5e, 0x2a, 0xea, 0xec,
    0xec, 0xd4, 0x46, 0xd0, 0xc2, 0x41, 0x84, 0x11, 0xa2, 0x7d, 0x1c, 0xea,
    0x66, 0x67, 0x57, 0x86, 0xb6, 0xd5, 0xf3, 0xda, 0xba, 0x13, 0x6f, 0xff,
    0xb9, 0xf9, 0x92, 0xeb, 0x77, 0xe9, 0x5c, 0xd7, 0xa7, 0x63, 0xfd, 0x75,
    0xc2, 0x6b, 0x36, 0x29, 0xd5, 0xd8, 0xf3, 0xad, 0xc7, 0x9a, 0x68, 0xa4,
    0x72, 0x69, 0xde, 0x8b, 0x43, 0x5f, 0xd1, 0x7e, 0xfe, 0x8c, 0x68, 0x7c,
    0x4a, 0x7d, 0x7a, 0x4e, 0x8c, 0x2a, 0xeb, 0x2a, 0x3c, 0x1e, 0x20, 0xf7,
    0x38, 0x27, 0x56, 0x73, 0xd3, 0x9a, 0x76, 0x56, 0x0d, 0x92, 0x5b, 0x1d,
    0x68, 0x74, 0x64, 0xbd, 0x35, 0xdb, 0xee, 0x93, 0x8f, 0x1d, 0xd5, 0x7f,
    0xf3, 0x2d, 0x00, 0x60, 0xf9, 0x52, 0xc9, 0x9f, 0x0e, 0xee, 0xb7, 0x7e,
    0xe2, 0x94, 0xee, 0x72, 0xac, 0x3e, 0x93, 0xa8, 0xce, 0x32, 0x5f, 0x63,
    0x9a, 0xf4, 0x5d, 0xb6, 0x85, 0x88, 0x72, 0xf4, 0x64, 0x11, 0x65, 0x08,
    0x22, 0xcd, 0xa6, 0x0a, 0xf9, 0x9a, 0xc1, 0xcd, 0x45, 0xcf, 0x7e, 0x73,
    0xbf, 0x89, 0x91, 0x61, 0x00, 0x69, 0x92, 0x78, 0xe2, 0xde, 0x2f, 0x5a,
    0x55, 0x3e, 0x6e, 0xc3, 0xba, 0x9a, 0x5c, 0x4f, 0x22, 0xdb, 0x43, 0x54,
    0x20, 0x42, 0x96, 0x20, 0x4f, 0x6f, 0x88, 0x20, 0x43, 0x35, 0x82, 0x84,
    0x34, 0x26, 0x4d, 0x68, 0x24, 0x4c, 0xcc, 0xb2, 0xed, 0x8e, 0xaf, 0x5a,
    0x3b, 0x70, 0x03, 0x80, 0x20, 0x0c, 0x7d, 0xf6, 0xa1, 0xc3, 0x4a, 0x8d,
    0xbc, 0xa4, 0x40, 0xa6, 0xf3, 0x72, 0xa3, 0x3c, 0x21, 0xb2, 0x88, 0xa9,
    0x85, 0x48, 0x30, 0x11, 0x20, 0x5e, 0xa1, 0x5e, 0xb9, 0xdc, 0xb1, 0x8b,
    0x84, 0x3b, 0x86, 0xdc, 0xf5, 0xe3, 0xdf, 0x08, 0x9b, 0x58, 0x75, 0xa9,
    0x64, 0x6a, 0xf8, 0x24, 0xd8, 0x7e, 0xdb, 0x9d, 0xf6, 0xfc, 0xe0, 0x88,
    0xd1, 0x52, 0x5e, 0xa3, 0x85, 0xb0, 0x40, 0x23, 0x06, 0x32, 0xd4, 0x47,
    0x99, 0x0c, 0xd1, 0x28, 0x73, 0x2a, 0x45, 0xad, 0xce, 0x72, 0x91, 0x89,
    0x19, 0x5a, 0xf6, 0x0c, 0xb9, 0xed, 0x91, 0x26, 0x1a, 0x45, 0x6a, 0x4d,
    0xf4, 0xf8, 0x2f, 0x3e, 0xef, 0xcd, 0x5f, 0xdf, 0x6e, 0xe6, 0xec, 0x6b,
    0x60, 0xe0, 0x53, 0x77, 0xda, 0xf5, 0xc8, 0x11, 0x17, 0x97, 0x5b, 0xd5,
    0xb0, 0xb2, 0x4c, 0x03, 0x09, 0xff, 0x7c, 0x9a, 0xd2, 0x7b, 0xf0, 0x3f,
    0x38, 0x16, 0x12, 0xc7, 0x29, 0x8b, 0xd3, 0xcd, 0x2e, 0xe5, 0x6c, 0xbf,
    0xfb, 0x1b, 0x82, 0xf7, 0xd1, 0x53, 0x3f, 0xd9, 0x67, 0x75, 0xe5, 0xa4,
    0xad, 0xeb, 0x16, 0x8d, 0x3e, 0x79, 0x40, 0x71, 0xf8, 0x32, 0x7e, 0xed,
    0x27, 0x6e, 0x55, 0xe8, 0xdb, 0xee, 0xd2, 0x14, 0xd5, 0x65, 0xa0, 0xcc,
    0x51, 0xd4, 0x23, 0xa4, 0x6f, 0xb1, 0xb0, 0x8f, 0x9d, 0x6d, 0xdc, 0x10,
    0xc7, 0x04, 0x8d, 0x86, 0xf1, 0x13, 0x47, 0xf5, 0xee, 0xdc, 0xed, 0xcc,
    0xaf, 0xee, 0x13, 0x4e, 0x9c, 0x94, 0xcf, 0x22, 0xa6, 0x35, 0xa8, 0x9a,
    0x7a, 0xfd, 0x79, 0x85, 0x0d, 0x1f, 0x37, 0xf2, 0x87, 0xef, 0x5a, 0x3e,
    0xf5, 0x17, 0x8b, 0x6f, 0x13, 0xc6, 0x04, 0x14, 0x9f, 0xe3, 0xe1, 0x61,
    0x8a, 0x01, 0x20, 0xf3, 0x05, 0x76, 0x3f, 0xc0, 0x4b, 0x0d, 0x7a, 0x2a,
    0x01, 0xba, 0xc9, 0x7e, 0x84, 0x7c, 0x0f, 0xad, 0x5d, 0x64, 0xdb, 0xc8,
    0xb4, 0x12, 0x66, 0x49, 0x52, 0xe2, 0x2a, 0x95, 0x49, 0xe6, 0xff, 0x4e,
    0xb4, 0x48, 0x81, 0x74, 0x84, 0xc3, 0x0f, 0xf3, 0x5b, 0x54, 0x23, 0x40,
    0x32, 0x4c, 0xa9, 0x8f, 0xf1, 0xad, 0xdc, 0x11, 0x92, 0xa9, 0xad, 0x50,
    0x2d, 0x13, 0xd7, 0xa8, 0xd7, 0x2f, 0x43, 0xef, 0x9d, 0x2d, 0x52, 0xfe,
    0x2f, 0xf3, 0x67, 0x59, 0x78, 0x87, 0xd6, 0x15, 0x3a, 0x30, 0xcd, 0x1f,
    0x87, 0xf8, 0x79, 0xc2, 0x32, 0x44, 0x00, 0x88, 0xff, 0xca, 0xf9, 0x35,
    0xfc, 0xfb, 0x46, 0xf6, 0xe6, 0x29, 0x24, 0x31, 0xf5, 0x25, 0x2a, 0x45,
    0x96, 0x67, 0x28, 0x4f, 0x52, 0xbe, 0xc0, 0xca, 0x7f, 0x88, 0xe6, 0xe9,
    0x4a, 0xe8, 0xa6, 0xd1, 0x1c, 0x9f, 0x78, 0x88, 0x47, 0x2b, 0x94, 0x90,
    0xfe, 0x3f, 0x0c, 0xb5, 0xe3, 0xfc, 0xeb, 0x02, 0xaf, 0x7d, 0x94, 0xde,
    0x75, 0x6c, 0x2e, 0x90, 0xc9, 0x25, 0xe4, 0x62, 0x5a, 0xea, 0x14, 0x1a,
    0x74, 0xa7, 0xf4, 0x92, 0xc6, 0x9c, 0x7e, 0x99, 0xef, 0x1d, 0xe2, 0xf7,
    0x55, 0x8a, 0x48, 0xae, 0xf6, 0x35, 0x05, 0xc8, 0x62, 0xd5, 0x5e, 0xb6,
    0xde, 0xc5, 0xed, 0x6b, 0xd8, 0xd1, 0xc2, 0xda, 0x80, 0x28, 0xa6, 0xb8,
    0xc0, 0xc8, 0x9b, 0xbc, 0xfa, 0x24, 0x27, 0x13, 0xa6, 0x51, 0x45, 0x0a,
    0x57, 0x83, 0x01, 0x02, 0x64, 0xd0, 0x8a, 0x02, 0x72, 0x80, 0x3a, 0x2a,
    0x58, 0x41, 0x1d, 0x09, 0x57, 0xe6, 0x7f, 0x6b, 0xd8, 0xcb, 0x5d, 0x58,
    0xaf, 0x39, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae,
    0x42, 0x60, 0x82
};

QIcon MyLineEdit::iconOK = QIcon();
QIcon MyLineEdit::iconError = QIcon();
QIcon MyLineEdit::iconDefault = QIcon();

MyLineEdit::MyLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    // initialize icons
    QPixmap pixOk, pixError;

    pixOk.loadFromData(MyLineEdit::OK_ICON_DATA, sizeof(MyLineEdit::OK_ICON_DATA));
    MyLineEdit::iconOK.addPixmap(pixOk);

    pixError.loadFromData(MyLineEdit::ERROR_ICON_DATA, sizeof(MyLineEdit::ERROR_ICON_DATA));
    MyLineEdit::iconError.addPixmap(pixError);

    button = new QToolButton(this);
    // maximum size for the icons. Smaller icons will not be scaled up.
    button->setIconSize(ICON_SIZE);
    button->setCursor(Qt::ArrowCursor);
    button->setStyleSheet("QToolButton { border: none; padding: 0px; }");

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), button->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), button->sizeHint().height() + frameWidth * 2 + 2));

    //setIcon(MyLineEdit::DEFAULT);
}

MyLineEdit::~MyLineEdit()
{
    delete button;
}

void MyLineEdit::setIcon(State state)
{
    switch (state) {
    case MyLineEdit::OK:
        button->setIconSize(ICON_SIZE);
        button->setIcon(MyLineEdit::iconOK);
        break;
    case MyLineEdit::ERROR:
        button->setIconSize(ICON_SIZE);
        button->setIcon(MyLineEdit::iconError);
        break;
    default:
        button->setIconSize(QSize(0,0));
        button->setIcon(MyLineEdit::iconDefault);
        break;
    }
}

void MyLineEdit::resizeEvent(QResizeEvent *)
{
    QSize sz = button->sizeHint();

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ")\
                  .arg(button->sizeHint().width() + frameWidth + 1));

    // show the icon
    button->move(rect().right() - frameWidth - sz.width(),
                 (rect().bottom() + 1 - sz.height())/2);
}

void MyLineEdit::focusOutEvent(QFocusEvent *e)
{
    emit focusOut();
    QLineEdit::focusOutEvent(e);
}

