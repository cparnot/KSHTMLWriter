//
//  KSStyleSheetWriter.h
//
//  Copyright 2010-2012, Mike Abdullah and Karelia Software
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL MIKE ABDULLAH OR KARELIA SOFTWARE BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#define CSS_COMMENTS 1

#import "KSForwardingWriter.h"

typedef NS_OPTIONS(NSUInteger, KSStyleSheetOutputFormat) {
	kStyleSpaceAfterColon		= 0,			// foo: bar rather than foo:bar
	kStyleSpacesBetween			= (1 <<  0),	// spaces between declarations.
	kStyleLinesBetween			= (1 <<  1),	// newlines between declarations. Don't use both this and spacesBetween.
	kStyleEndingSemicolon		= (1 <<  2),	// if set, last declaration in block ends in unnecessary semicolon
	kStyleNewlineBeforeBrace	= (1 <<	 3),	// in declaration blocks, start { on new line. If not set, it's k&r style :-)
	kStyleIndent				= (1 <<  4),	// in declaration blocks, should lines be indented
	kStyleHighlightSections		= (1 <<  5),	// Chunks of ======== to highlight big sections
	kStyleLongSelectorForceBreak= (1 <<  6),	// #superLongSelector\n{ ... } even if not kStyleNewlineBeforeBrace
};

@class KSStyleWriter;


@interface KSStyleSheetWriter : KSForwardingWriter

@property KSStyleSheetOutputFormat outputFormat;

+ (NSString *)stringWithOutputFormat:(KSStyleSheetOutputFormat)format declarations:(void(^)(KSStyleWriter *))declarations; // no difference between last 2 since that involves { } wrapping

// Vends out a temporary style writer to you for writing declarations. Do NOT attempt to use the style writer beyond the block
- (void)writeSelector:(NSString *)selector declarations:(void (^)(KSStyleWriter *styleWriter))declarations;
- (void)writeSelector:(NSString *)selector declarationString:(NSString *)declarations;

- (void)writeMediaQuery:(NSString *)predicate declarations:(void (^)(KSStyleSheetWriter *styleWriter))declarations;
- (void)writeCommentLine:(NSString *)comment;      // \n afterward if appropriate.
- (void)writeCommentSection:(NSString *)comment;      // \n afterward if appropriate.
- (void)writeLine:(NSString *)line;      // \n afterward if appropriate.

@end