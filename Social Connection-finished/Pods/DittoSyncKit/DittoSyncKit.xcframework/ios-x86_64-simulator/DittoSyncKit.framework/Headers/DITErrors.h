//
//  DITErrors.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 23/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSString *__nonnull const DITDomain;

// clang-format off
// Taken from https://gist.github.com/bdash/bf29e26c429b78cc155f1a2e1d851f8b
#if __has_attribute(ns_error_domain)
#define DIT_ERROR_ENUM(type, name, domain) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wignored-attributes\"") \
    NS_ENUM(type, __attribute__((ns_error_domain(domain))) name) \
    _Pragma("clang diagnostic pop")
#else
#define DIT_ERROR_ENUM(type, name, domain) NS_ENUM(type, name)
#endif
// clang-format on

/**
 All of the error code values for `NSError`'s with the `DITDomain` domain.
 */
typedef DIT_ERROR_ENUM(NSInteger, DITErrorCode, DITDomain){
    /**
     An error occurred with the storage backend.
     */
    DITStorageInteralError = 10,

    /**
     The document could not be found.
    */
    DITDocumentNotFoundError = 11,

    /**
     The provided document content failed to be encoded.
    */
    DITDocumentContentEncodingFailed = 12,

    /**
     The request to get transport diagnostics failed.
    */
    DITTransportDiagnosticsUnavailable = 13,

    /**
     Decoding of transport diagnostics data failed.
    */
    DITTransportDiagnosticsDecodingFailed = 14,

    /**
     The attachment's data could not be retrieved.
     */
    DITAttachmentDataRetrievalError = 15,

    /**
     The attachment file failed to be copied.
     */
    DITAttachmentFileCopyError = 16,
};
