//
//  DITDocumentPath+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@interface DITDocumentPath ()
@property (nonatomic, readonly) NSDictionary<NSString *, id> *value;
@property (nonatomic, readonly) NSString *docID;
/**
 Contains either a string path component or an integer (as an NSNumber),
 referencing an array index.
 */
@property (nonatomic, readonly) NSArray *pathComponents;

- (instancetype)initWithValue:(NSDictionary<NSString *, id> *)value
                   documentID:(NSString *)docID
                         path:(NSArray *)pathComponents;

+ (instancetype)documentPathFrom:(DITDocumentPath *)path appending:(NSObject *)suffix;
@end

NS_ASSUME_NONNULL_END
