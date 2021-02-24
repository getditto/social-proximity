//
//  DITWriteTransactionPendingIDSpecificOperation+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DITWriteTransaction;

NS_ASSUME_NONNULL_BEGIN

@interface DITWriteTransactionPendingIDSpecificOperation ()

@property (nonatomic, readonly) NSString *docID;
@property (nonatomic, readonly) NSString *collectionName;
// This holds a `DittoHandleWrapper` reference, so we don't have to hold another reference explicity
// as we are already implicitly holding one here.
@property (nonatomic, readonly) DITWriteTransaction *baseTransaction;

- (instancetype)initWithDocID:(NSString *)docID
               collectionName:(NSString *)collectionName
              baseTransaction:(DITWriteTransaction *)baseTransaction;

- (void)updateUsingData:(NSData *)data;
@end

NS_ASSUME_NONNULL_END
