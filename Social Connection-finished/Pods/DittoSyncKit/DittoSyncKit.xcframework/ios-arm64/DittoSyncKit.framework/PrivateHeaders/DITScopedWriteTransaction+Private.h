//
//  DITScopedWriteTransaction+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DITWriteTransaction;

NS_ASSUME_NONNULL_BEGIN

@interface DITScopedWriteTransaction ()
@property (nonatomic, readonly) DITWriteTransaction *baseTransaction;

- (instancetype)initWithBaseTransaction:(DITWriteTransaction *)baseTransaction
                         collectionName:(NSString *)collectionName;

- (nullable NSString *)insertCBORData:(NSData *)data
                               withID:(nullable NSString *)id
                            isDefault:(BOOL)isDefault
                                error:(NSError *_Nullable __autoreleasing *)error;
@end

NS_ASSUME_NONNULL_END
