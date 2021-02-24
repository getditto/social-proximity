//
//  DITAttachmentToken+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 10/03/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@interface DITAttachmentToken ()

@property (nonatomic, readonly) NSData *id;
@property (nonatomic, readonly) NSUInteger len;
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *metadata;

- (nullable instancetype)initWithInfo:(NSDictionary<NSString *, id> *)info;

@end

NS_ASSUME_NONNULL_END
