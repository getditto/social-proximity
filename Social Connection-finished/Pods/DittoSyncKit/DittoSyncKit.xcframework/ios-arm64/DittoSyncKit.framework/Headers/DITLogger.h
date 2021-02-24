//
//  DITLogger.h
//  DittoSyncKit
//
//  Created by Daniel Henry-Mantilla on 03/12/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#ifndef DITDittoLogger_h
#define DITDittoLogger_h

#import <Foundation/Foundation.h>

#import <DittoSyncKit/DITLogLevel.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Class with static methods to customize the logging behavior from Ditto.
 */
@interface DITLogger : NSObject

/**
  Whether the logger is currently enabled.
 */
@property(class, nonatomic, assign) BOOL enabled;

/**
 The minimum log level at which logs will be logged.
 
 For example if this is set to `DITLogLevel.Warning`, then only logs that are logged with
 the `Warning` or `Error` log levels will be shown.
 */
@property(class, nonatomic, assign) enum DITLogLevel minimumLogLevel;


/**
 Represents whether or not emojis should be used as the log level indicator in the logs.
 */
@property(class, nonatomic, assign) BOOL emojiLogLevelHeadingsEnabled;

/**
 Registers a file path where logs will be written to, whenever Ditto wants
 to issue a log (on _top_ of emitting the log to the console).

 @param logFile can be `nil`, in which case the current logging file, if any,
 is unregistered, otherwise, the file path must be within an already existing directory.
 */
+ (void)setLogFile:(nullable NSString *)logFile;

/**
 Registers a file path where logs will be written to, whenever Ditto wants
 to issue a log (on _top_ of emitting the log to the console).

 @param logFile can be `nil`, in which case the current logging file, if any,
 is unregistered, otherwise, the file path must be within an already existing directory.
 */
+ (void)setLogFileURL:(nullable NSURL *)logFile;

/**
 Registers a callback for a fully customizable way of handling log "events" from the logger
 (on _top_ of logging to the console, and to a file, if any).
 
 @param logCallback a block that can be `nil`, in which case the current callback, if any, is unregistered.
 Otherwise it is called each time a log statement is issued by Ditto (after filtering by log level), which can happen
 in parallel; the block must thus be thread-safe.
 */
+ (void)setCustomLogCallback:(nullable void (^)(enum DITLogLevel logLevel, NSString * logMessage))logCallback;

@end
NS_ASSUME_NONNULL_END
#endif /* DITDittoLogger_h */
