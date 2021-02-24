//
//  DITSingleDocumentLiveQueryEvent+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DITDocument;

NS_ASSUME_NONNULL_BEGIN

@interface DITSingleDocumentLiveQueryEvent ()

- (instancetype)initWithIsInitial:(BOOL)isInitial oldDocument:(nullable DITDocument *)oldDocument;

@end

NS_ASSUME_NONNULL_END
