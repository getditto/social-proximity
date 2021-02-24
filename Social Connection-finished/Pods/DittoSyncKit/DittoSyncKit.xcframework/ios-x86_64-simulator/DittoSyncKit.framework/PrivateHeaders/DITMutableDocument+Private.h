//
//  DITMutableDocument+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import "dittoffi.h"

@class DITUpdateResult;

NS_ASSUME_NONNULL_BEGIN

@interface DITMutableDocument ()
// This will be freed as part of the update process that uses these `DittoMutableObject`s
@property (nonatomic, readonly, unsafe_unretained) CDocument_t *documentHandle;
@property (nonatomic, readonly) NSMutableArray<DITUpdateResult *> *results;

- (instancetype)initWithDocumentHandle:(CDocument_t *)documentHandle;
@end

NS_ASSUME_NONNULL_END
