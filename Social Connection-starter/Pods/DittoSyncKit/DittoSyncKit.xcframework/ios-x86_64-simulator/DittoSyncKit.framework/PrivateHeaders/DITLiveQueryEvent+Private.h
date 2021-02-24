//
//  DITLiveQueryEvent+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DITDocument;
@class DITLiveQueryMove;

NS_ASSUME_NONNULL_BEGIN

@interface DITLiveQueryEvent ()

- (instancetype)initWithOldDocuments:(NSArray<DITDocument *> *)oldDocs
                          insertions:(NSArray<NSNumber *> *)insertions
                           deletions:(NSArray<NSNumber *> *)deletions
                             updates:(NSArray<NSNumber *> *)updates
                               moves:(NSArray<DITLiveQueryMove *> *)moves;

- (instancetype)initInitial;

@end

NS_ASSUME_NONNULL_END
