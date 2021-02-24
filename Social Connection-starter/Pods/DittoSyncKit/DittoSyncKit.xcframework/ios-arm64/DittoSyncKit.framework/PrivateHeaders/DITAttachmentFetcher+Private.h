//
//  DITAttachmentFetcher+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 11/03/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DITAttachmentFetchEvent;
@class DITAttachmentToken;
@class DittoHandleWrapper;

NS_ASSUME_NONNULL_BEGIN

@interface DITAttachmentFetcher ()

@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readonly) void (^onFetchEvent)(DITAttachmentFetchEvent *);
@property (nonatomic, readonly) DITAttachmentToken *token;
@property (nonatomic, readonly) uint64_t cancelToken;

- (instancetype)initWithAttachmentToken:(DITAttachmentToken *)attachmentToken
                           onFetchEvent:(void (^)(DITAttachmentFetchEvent *))onFetchEvent
                     dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper;

@end

NS_ASSUME_NONNULL_END
