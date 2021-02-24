//
//  DITWriteTransactionResult+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 05/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@interface DITWriteTransactionResultInserted ()
- (instancetype)initWithDocID:(NSString *)docID collectionName:(NSString *)collectionName;
@end

@interface DITWriteTransactionResultRemoved ()
- (instancetype)initWithDocID:(NSString *)docID collectionName:(NSString *)collectionName;
@end

@interface DITWriteTransactionResultEvicted ()
- (instancetype)initWithDocID:(NSString *)docID collectionName:(NSString *)collectionName;
@end

@interface DITWriteTransactionResultUpdated ()
- (instancetype)initWithDocID:(NSString *)docID collectionName:(NSString *)collectionName;
@end

NS_ASSUME_NONNULL_END
