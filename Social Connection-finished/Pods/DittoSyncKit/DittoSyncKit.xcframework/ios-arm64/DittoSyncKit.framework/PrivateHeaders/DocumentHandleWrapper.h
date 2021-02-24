//
//  DocumentHandleWrapper.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 13/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "dittoffi.h"

struct Ditto_Document;

NS_ASSUME_NONNULL_BEGIN

@interface DocumentHandleWrapper : NSObject
@property (nonatomic, readonly, unsafe_unretained) CDocument_t *documentHandle;

- (instancetype)initWithDocumentHandle:(CDocument_t *)documentHandle;
@end

NS_ASSUME_NONNULL_END
