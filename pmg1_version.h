/******************************************************************************
* @file pmg1_version.h
*
* @brief This file defines the version details of the PMG1 Code Example.
*

*******************************************************************************/

#ifndef _PMG1_VERSION_H_
#define _PMG1_VERSION_H_

/**
   @brief Major version of the PMG1 CE.
 */
#define PMG1_CE_MAJOR_VERSION                                (3)

/**
   @brief Minor version of the PMG1 CE.
 */
#define PMG1_CE_MINOR_VERSION                                (1)

/**
   @brief Patch version of the PMG1 CE.
 */
#define PMG1_CE_PATCH_VERSION                                (0)

/**
   @brief Build number of the PMG1 CE. Base Build number: 0000
          When the value reaches 9999 this shall be reset to 0.
 */
#define PMG1_CE_BUILD_NUMBER                                 (12)

/**
 *  @brief Composite PMG1 CE version value.
 *
 *  PMG1 CE version value. This is a 4 byte value with the following format:
 *  Bytes 1-0: Build number
 *  Byte    2: Patch version
 *  Byte 3 (Bits 0:3): Minor Version
 *  Byte 3 (Bits 4:7): Major Version
 */
#define PMG1_CE_BASE_VERSION                                             \
        ((PMG1_CE_MAJOR_VERSION << 28) | (PMG1_CE_MINOR_VERSION << 24) |      \
        (PMG1_CE_PATCH_VERSION << 16) | (PMG1_CE_BUILD_NUMBER))

#endif /* _PMG1_VERSION_H_ */

/* End of file */
