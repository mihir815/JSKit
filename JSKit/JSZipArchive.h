//
//  JSZipArchive.h
//  JSKit
//
//  Created by 정재성 on 2014. 6. 4..
//  Copyright (c) 2014년 Jaesung Jung. All rights reserved.
//

@import Foundation.NSObject;

#if defined(__LP64__) && __LP64__
# define PROGRESS_TYPE double
# define PROGRESS_IS_DOUBLE 1
#else
# define PROGRESS_TYPE float
# define PROGRESS_IS_DOUBLE 0
#endif

typedef PROGRESS_TYPE JSFloat;

typedef NS_ENUM(NSInteger, JSZipArchiveError) {
    JSZipArchiveErrorFileOpen = 1,
    JSZipArchiveErrorFileIsNotOpened,
    JSZipArchiveErrorBadZipFile,
    JSZipArchiveErrorBadParameter,
    JSZipArchiveErrorBadPassword,
    JSZipArchiveErrorInternalError,
    JSZipArchiveErrorCRC,
    JSZipArchiveErrorUnknown,
};

@class JSZipArchive;
@class JSUnzippedData;

@protocol JSZipArchiveDelegate <NSObject>

@optional
- (void)zipArchive:(JSZipArchive *)zipArchive willBeginUnzipOnZipFileName:(NSString *)fileName;
- (void)zipArchive:(JSZipArchive *)zipArchive didEndUnzipOnZipFileName:(NSString *)fileName;
- (void)zipArchive:(JSZipArchive *)zipArchive updateProgress:(JSFloat)progress onUnzipFileName:(NSString *)unzipFileName;

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface JSZipArchive : NSObject

@property (nonatomic, readonly) NSString *zipFilePath;
@property (nonatomic, readonly) NSString *zipFileName;
@property (nonatomic, readonly) NSString *comment;
@property (nonatomic, strong)   NSString *password;

@property (nonatomic, readonly) BOOL encrypted;

@property (nonatomic, readonly) BOOL isOpened;

@property (nonatomic, weak) id<JSZipArchiveDelegate> delegate;

/*!
 * Open an existing zip file ready for unzip.
 *
 * @params path Path of zip file.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)openWithPath:(NSString *)path error:(NSError **)error;

/*!
 * Open an existing zip file ready for unzip.
 *
 * @params path Path of the zip file.
 * @params password Password of the zip file.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)openWithPath:(NSString *)path password:(NSString *)password error:(NSError **)error;

/*!
 * Unzip all files in the zip archive into the specified path.
 *
 * @params path Path of unzip.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)unzipToPath:(NSString *)path error:(NSError **)error;

/*!
 * Unzip all files in the zip archive into the specified path.
 *
 * @params path Path of unzip.
 * @params overwirte If yes, existing files be overwite.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)unzipToPath:(NSString *)path overwrite:(BOOL)overwrite error:(NSError **)error;

/*!
 * Unzip all files in the zip archive into the specified path.
 *
 * @params path Path of unzip.
 * @params createFolder If yes, create root folder for unzip.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)unzipToPath:(NSString *)path createFolder:(BOOL)createFolder error:(NSError **)error;

/*!
 * Unzip all files in the zip archive into the specified path.
 *
 * @params path Path of unzip.
 * @params createFolder If yes, create root folder for unzip.
 * @params overwirte If yes, existing files be overwite.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)unzipToPath:(NSString *)path createFolder:(BOOL)createFolder overwrite:(BOOL)overwrite error:(NSError **)error;

/*!
 * Unzip all files in the zip archive into the memory.
 *
 * @return JSUnzipData array that contains unzip data.
 */
- (NSArray *)unzipToArray;

/*!
 * Unzip first file in the zip archive into the memory.
 *
 * @params indexSet index set for zip content.
 *
 * @return A JSUnzipData.
 */
- (JSUnzippedData *)unzipFirstFile;

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface JSUnzippedData : NSObject

@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSData *unzippedData; // If isDirectory property is true, unzippedData is nil.
@property (nonatomic, strong) NSDate *modificationDate;
@property (nonatomic, strong) NSArray *childFiles;
@property (nonatomic, assign) BOOL isDirectory;

@end