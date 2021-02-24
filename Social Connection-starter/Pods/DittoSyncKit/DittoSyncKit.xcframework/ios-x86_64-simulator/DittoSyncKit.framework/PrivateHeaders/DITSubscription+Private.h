//
//  DITSubscription+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DittoHandleWrapper;

NS_ASSUME_NONNULL_BEGIN

@interface DITSubscription ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;

- (instancetype)initWithQuery:(NSString *)query
               collectionName:(NSString *)collectionName
           dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper;
@end

NS_ASSUME_NONNULL_END
