//
//  DITWriteTransactionPendingCursorOperation+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import "dittoffi.h"

@class DITWriteTransaction;

struct Ditto_OrderDefinition;
struct COrderByParam;

NS_ASSUME_NONNULL_BEGIN

@interface DITWriteTransactionPendingCursorOperation ()
@property (nonatomic, readonly) NSString *query;
@property (nonatomic, readonly) NSString *collectionName;
@property (nonatomic, readwrite) int limit;
@property (nonatomic, readwrite) uint offset;
// orderDefinitions will eventually be replaced with orderBy, but has been kept for now to
// facilitate incremental refactoring.
@property (nonatomic, readwrite, nullable) COrderDefinition_t *orderDefinitions;
@property (nonatomic, readwrite) uint orderDefinitionsCount;
@property (nonatomic, readwrite, nullable) COrderByParam_t *orderBy;
@property (nonatomic, readwrite) uint orderByCount;
// This holds a `DittoHandleWrapper` reference, so we don't have to hold another reference explicity
// as we are already implicitly holding one here.
@property (nonatomic, readonly) DITWriteTransaction *baseTransaction;
@property (nonatomic, readwrite, nullable) NSError *error;

- (instancetype)initWithQuery:(NSString *)query
               collectionName:(NSString *)collectionName
              baseTransaction:(DITWriteTransaction *)baseTransaction;

@end

NS_ASSUME_NONNULL_END
