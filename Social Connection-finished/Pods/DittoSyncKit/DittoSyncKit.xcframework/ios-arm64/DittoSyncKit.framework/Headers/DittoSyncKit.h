//
//  DittoSyncKit.h
//  Ditto
//
//  Created by Hamilton Chapman on 05/02/2019.
//  Copyright © 2019 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for DittoSyncKit.
FOUNDATION_EXPORT double DittoSyncKitVersionNumber;

//! Project version string for DittoSyncKit.
FOUNDATION_EXPORT const unsigned char DittoSyncKitVersionString[];

// General
#import <DittoSyncKit/DITDittoSyncKit.h>
#import <DittoSyncKit/DITDittoSyncKitDelegate.h>
#import <DittoSyncKit/DITErrors.h>
#import <DittoSyncKit/DITIdentity.h>
#import <DittoSyncKit/DITLogger.h>
#import <DittoSyncKit/DITLogLevel.h>

// Store
#import <DittoSyncKit/DITAttachment.h>
#import <DittoSyncKit/DITAttachmentFetcher.h>
#import <DittoSyncKit/DITAttachmentFetchEvent.h>
#import <DittoSyncKit/DITAttachmentToken.h>
#import <DittoSyncKit/DITCollection.h>
#import <DittoSyncKit/DITDocument.h>
#import <DittoSyncKit/DITDocumentPath.h>
#import <DittoSyncKit/DITLiveQuery.h>
#import <DittoSyncKit/DITLiveQueryEvent.h>
#import <DittoSyncKit/DITLiveQueryMove.h>
#import <DittoSyncKit/DITMutableDocument.h>
#import <DittoSyncKit/DITMutableDocumentPath.h>
#import <DittoSyncKit/DITPendingCursorOperation.h>
#import <DittoSyncKit/DITPendingIDSpecificOperation.h>
#import <DittoSyncKit/DITScopedWriteTransaction.h>
#import <DittoSyncKit/DITSignalNext.h>
#import <DittoSyncKit/DITSingleDocumentLiveQueryEvent.h>
#import <DittoSyncKit/DITSortDirection.h>
#import <DittoSyncKit/DITStore.h>
#import <DittoSyncKit/DITSubscription.h>
#import <DittoSyncKit/DITUpdateResult.h>
#import <DittoSyncKit/DITWriteTransaction.h>
#import <DittoSyncKit/DITWriteTransactionPendingCursorOperation.h>
#import <DittoSyncKit/DITWriteTransactionPendingIDSpecificOperation.h>
#import <DittoSyncKit/DITWriteTransactionResult.h>

// Transport
#import <DittoSyncKit/DITPeersObserver.h>
#import <DittoSyncKit/DITRemotePeer.h>
#import <DittoSyncKit/DITTransport.h>
#import <DittoSyncKit/DITTransportCondition.h>
#import <DittoSyncKit/DITTransportDiagnostics.h>
#import <DittoSyncKit/DITTransportSnapshot.h>
