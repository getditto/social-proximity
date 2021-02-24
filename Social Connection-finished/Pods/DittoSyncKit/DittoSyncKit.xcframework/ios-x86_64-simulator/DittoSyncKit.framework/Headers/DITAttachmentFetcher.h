//
//  DITAttachmentFetcher.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 11/03/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 These objects are returned by calls to `fetchAttachment` on `DITCollection`s. They must be kept
 alive for as long as you wish to observe updates about the associated attachment.
 */
@interface DITAttachmentFetcher : NSObject

/**
 Stops fetching the fetcher's associated attachment and cleans up any associated resources.

 Note that you are not required to call `stop` once your attachment fetch operation has finished.
 The method primarily exists to allow you to cancel an attachment fetch request while it is ongoing
 if you no longer wish for the attachment to be made available locally to the device.

 Niling out any reference(s) you have to the attachment fetcher will also lead to the attachment
 fetch operation being stopped.
 */
- (void)stop;

@end

NS_ASSUME_NONNULL_END
