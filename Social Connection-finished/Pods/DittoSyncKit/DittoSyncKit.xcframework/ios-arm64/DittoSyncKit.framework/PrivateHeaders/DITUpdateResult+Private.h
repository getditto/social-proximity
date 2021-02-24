//
//  DITUpdateResult+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 04/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@interface DITUpdateResultSet ()
- (instancetype)initWithDocID:(NSString *)docID path:(NSString *)path value:(id)value;
@end

@interface DITUpdateResultRemoved ()
- (instancetype)initWithDocID:(NSString *)docID path:(NSString *)path;
@end

@interface DITUpdateResultReplacedWithCounter ()
- (instancetype)initWithDocID:(NSString *)docID path:(NSString *)path;
@end

@interface DITUpdateResultIncremented ()
- (instancetype)initWithDocID:(NSString *)docID path:(NSString *)path amount:(double)amount;
@end

@interface DITUpdateResultPushed ()
- (instancetype)initWithDocID:(NSString *)docID path:(NSString *)path value:(id)value;
@end

@interface DITUpdateResultPopped ()
- (instancetype)initWithDocID:(NSString *)docID path:(NSString *)path value:(id)value;
@end

@interface DITUpdateResultInserted ()
- (instancetype)initWithDocID:(NSString *)docID path:(NSString *)path value:(id)value;
@end

NS_ASSUME_NONNULL_END
