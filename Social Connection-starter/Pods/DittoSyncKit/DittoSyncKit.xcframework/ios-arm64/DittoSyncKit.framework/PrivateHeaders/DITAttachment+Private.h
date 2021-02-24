//
//  DITAttachment+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 10/03/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@class DittoHandleWrapper;

struct AttachmentHandle;

@interface DITAttachment ()

@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSData *id;
@property (nonatomic, readonly) NSUInteger len;
@property (nonatomic, readonly) struct AttachmentHandle *handle;
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readwrite, nullable) NSString *path;

- (instancetype)initWithID:(NSData *)id
                       len:(NSUInteger)len
                  metadata:(NSDictionary<NSString *, NSString *> *)metadata
                    handle:(struct AttachmentHandle *)handle
        dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper;

@end

NS_ASSUME_NONNULL_END
