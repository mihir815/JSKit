//
//  JSZipArchive.h
//
//  Copyright (c) 2014 Jaesung Jung
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to
//  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//  the Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

@import Foundation.NSObject;
@import Foundation.NSData;
@import Foundation.NSDate;
@import Foundation.NSError;

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
    JSZipArchiveErrorWrongArchiveMode,
    JSZipArchiveErrorFileIsNotExist,
    JSZipArchiveErrorUnknown,
};

typedef NS_ENUM(NSInteger, JSZIpArchiveCompressionLevel) {
    JSZIpArchiveCompressionLevelNoCompression       = 0,
    JSZIpArchiveCompressionLevelBestSpeed           = 1,
    JSZIpArchiveCompressionLevelBestCompression     = 9,
    JSZIpArchiveCompressionLevelDefaultCompression  = -1
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
@property (nonatomic, readonly) NSUInteger fileCount;

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
 * Close opened file.
 */
- (void)close;

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
 * Unzip file at given index.
 *
 * @params index index of file.
 *
 * @return A JSUnzipData instance.
 */
- (JSUnzippedData *)unzipFileAtIndex:(NSUInteger)index;

/*!
 * Returns file index of given offset.
 *
 * @params offset file offset.
 *
 * @return file index of offset.
 */
- (NSUInteger)indexOfFileOffset:(NSUInteger)offset;

/*!
 * Returns file offset at given index.
 *
 * @params index index of file.
 *
 * @return file offset at index.
 */
- (NSUInteger)offsetAtIndex:(NSUInteger)index;

/*!
 * Create zip file.
 *
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)createZipFile:(NSString *)zipFilePath error:(NSError **)error;

/*!
 * Create encrypted zip file using given password.
 *
 * @params password Password for encrypted zip file.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)createZipFile:(NSString *)zipFilePath password:(NSString *)password error:(NSError **)error;

/*!
 * Create encrypted zip file using given password.
 *
 * @params password Password for encrypted zip file.
 * @params overwrite If yes, existing files be overwite.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)createZipFile:(NSString *)zipFilePath password:(NSString *)password overwrite:(BOOL)overwrite error:(NSError **)error;

/*!
 * Zip files into the specified path.
 *
 * @params filePath File path for compress.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)zipFilePath:(NSString *)filePath error:(NSError **)error;

/*!
 * Zip files into the specified path.
 *
 * @params filePath File path for compress.
 * @params level Compress level.
 * @params error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information.
 */
- (void)zipFilePath:(NSString *)filePath level:(JSZIpArchiveCompressionLevel)level error:(NSError **)error;

@end

NS_CLASS_AVAILABLE_IOS(2_0) @interface JSUnzippedData : NSObject

@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSData *data; // If isDirectory property is true, unzippedData is nil.
@property (nonatomic, strong) NSDate *modificationDate;
@property (nonatomic, strong) NSArray *childFiles;
@property (nonatomic, assign) BOOL isDirectory;
@property (nonatomic, assign) NSUInteger offset;

@end
