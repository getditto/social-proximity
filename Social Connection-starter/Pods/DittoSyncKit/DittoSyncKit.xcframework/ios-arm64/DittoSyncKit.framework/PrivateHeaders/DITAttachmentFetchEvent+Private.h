//
//  DITAttachmentFetchEvent+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 10/03/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DITAttachment;

NS_ASSUME_NONNULL_BEGIN

@interface DITAttachmentFetchEventCompleted ()
- (instancetype)initWithAttachment:(DITAttachment *)attachment;
@end

@interface DITAttachmentFetchEventProgress ()
- (instancetype)initWithDownloadedBytes:(NSUInteger)downloadedBytes
                             totalBytes:(NSUInteger)totalBytes;
@end

@interface DITAttachmentFetchEventDeleted ()
- (instancetype)init;
@end

NS_ASSUME_NONNULL_END
