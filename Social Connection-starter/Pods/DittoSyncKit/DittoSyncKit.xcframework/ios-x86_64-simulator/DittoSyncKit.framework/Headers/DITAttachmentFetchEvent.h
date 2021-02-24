//
//  DITAttachmentFetchEvent.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 10/03/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITAttachment;
@class DITAttachmentFetchEventCompleted;
@class DITAttachmentFetchEventProgress;
@class DITAttachmentFetchEventDeleted;

/**
 The types of attachment fetch events that can be delivered to an attachment fetcher's
 `onFetchEvent` block.
 */
typedef NS_ENUM(NSUInteger, DITAttachmentFetchEventType) {
    DITAttachmentFetchEventTypeCompleted = 0,
    DITAttachmentFetchEventTypeProgress,
    DITAttachmentFetchEventTypeDeleted,
};

NS_ASSUME_NONNULL_BEGIN

/**
 A representation of the events that can occur in relation to an attachment fetch.

 There are three different attachment fetch events: `Completed`, `Progress`, or `Deleted`.

 There will be at most one `Completed` or `Deleted` event per attachment fetch. There can be many
 `Progress` events delivered for each attachment fetch.

 Updates relating to an attachment fetch are delivered by registering a `DITAttachmentFetcher`
 through a call to `fetchAttachment` on a `DITCollection` instance.
 */
@interface DITAttachmentFetchEvent : NSObject

/**
 The attachment fetch event's type.

 Check this value before using one of `asCompleted`, `asProgress`, or `asDeleted` to ensure that you
 get a richer attachment fetch event object of the correct type.
 */
@property (nonatomic, readonly) DITAttachmentFetchEventType type;

/**
 Return the attachment fetch event object as a `DITAttachmentFetchEventCompleted` object.

 @return A `DITAttachmentFetchEventCompleted` object or `nil` if the attachment's fetch event is not
 completed.
 */
- (nullable DITAttachmentFetchEventCompleted *)asCompleted;

/**
 Return the attachment fetch event object as a `DITAttachmentFetchEventProgress` object.

 @return A `DITAttachmentFetchEventProgress` object or `nil` if the attachment's fetch event is not
 progress.
 */
- (nullable DITAttachmentFetchEventProgress *)asProgress;

/**
 Return the attachment fetch event object as a `DITAttachmentFetchEventDeleted` object.

 @return A `DITAttachmentFetchEventDeleted` object or `nil` if the attachment's fetch event is not deleted.
 */
- (nullable DITAttachmentFetchEventDeleted *)asDeleted;

@end

/**
 An attachment fetch event used when the attachment's download has completed.
 */
@interface DITAttachmentFetchEventCompleted : DITAttachmentFetchEvent

/**
 The complete attachment.
 */
@property (nonatomic, readonly) DITAttachment *attachment;

@end

/**
 An attachment fetch event used when the attachment's download progressed but is not yet complete.
 */
@interface DITAttachmentFetchEventProgress : DITAttachmentFetchEvent

/**
 The size of the attachment that was successfully downloaded, in bytes.
 */
@property (nonatomic, readonly) NSUInteger downloadedBytes;

/**
 The full size of the attachment, if it were complete.
 */
@property (nonatomic, readonly) NSUInteger totalBytes;

@end

/**
 An attachment fetch event used when the attachment is deleted.
 */
@interface DITAttachmentFetchEventDeleted : DITAttachmentFetchEvent
@end

NS_ASSUME_NONNULL_END
