//
//  HandleWrapper.h
//  DittoTransportsObjC
//
//  Created by Thomas Karpiniec on 31/3/20.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A generic handle for a Rust transport. Use this to send platform events to Rust, and dealloc to shut down.
@interface TransportHandleWrapper : NSObject

/// Wrap a raw handle pointer from Rust. We (the SDK) own this exclusively and are responsible for freeing it.
/// Pass in a destructor block that will call the corresponding free function. It will be invoked on dealloc.
- (instancetype)initWithHandle:(void *)handle destructor:(void (^)(void))destructor;

/// Borrow the raw pointer to send a method to the platform. The raw handle pointer should only ever be used
/// within the passed block, to ensure we do not use it after it has been deallocated.
- (void)withHandle:(void (^)(void * handle))action;

@end

NS_ASSUME_NONNULL_END
