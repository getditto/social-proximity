//
//  DITAttachment.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 10/03/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents an attachment and can be used to insert the associated attachment into a document at a
 specific key.
 */
@interface DITAttachment : NSObject

/**
 The attachment's metadata.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 Returns the attachment's data.

 @param error On input, a pointer to an error object. If an error occurs, this pointer
 is set to an actual error object containing the error information. You may specify nil for this
 parameter if you do not want the error information.

 @return The attachment's data.
 */
- (NSData *)getData:(NSError *_Nullable __autoreleasing *)error;

/**
 Copies the attachment to the specified file path.

 @param path The path that the attachment should be copied to.
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an
 actual error object containing the error information. You may specify nil for this parameter if you
 do not want the error information.

 @return A boolean indicating whether or not the attachment file was successfully copied.
 */
- (BOOL)copyToPath:(NSString *)path error:(NSError *_Nullable __autoreleasing *)error;

@end

NS_ASSUME_NONNULL_END
