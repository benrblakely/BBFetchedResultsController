//  Copyright 2013 Ben Blakely. All rights reserved.
//  See included License file for licensing information.

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "BBFetchedResultsIndexPath.h"

@protocol BBFetchedResultsControllerDelegate;

@interface BBFetchedResultsController : NSObject

@property (nonatomic, readonly) NSFetchRequest *fetchRequest;
@property (nonatomic, readonly) NSManagedObjectContext *managedObjectContext;
@property (nonatomic, readonly) NSString *sectionNameKeyPath; // If specified, must point to a persisent attribute.
@property (nonatomic, weak) id<BBFetchedResultsControllerDelegate> delegate;
@property (nonatomic, readonly) NSArray *fetchedObjects;
@property (nonatomic, readonly) NSArray *sectionIndexTitles;
@property (nonatomic, readonly) NSArray *sections;

- (id)initWithFetchRequest:(NSFetchRequest *)fetchRequest managedObjectContext:(NSManagedObjectContext *)context sectionNameKeyPath:(NSString *)sectionNameKeyPath;

- (BOOL)performFetch:(NSError **)error;

- (id)objectAtIndexPath:(BBFetchedResultsIndexPath *)indexPath;

-(BBFetchedResultsIndexPath *)indexPathForObject:(id)object;

- (NSString *)sectionIndexTitleForSectionName:(NSString *)sectionName;

- (NSInteger)sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)sectionIndex;

@end

@protocol BBFetchedResultsSectionInfo

@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *indexTitle;
@property (nonatomic, readonly) NSUInteger numberOfObjects;

@end

@protocol BBFetchedResultsControllerDelegate <NSObject>

typedef enum : NSInteger {
	BBFetchedResultsChangeInsert = 1,
	BBFetchedResultsChangeDelete,
	BBFetchedResultsChangeMove,
	BBFetchedResultsChangeUpdate,
} BBFetchedResultsChangeType;

@optional

- (void)controllerWillChangeContent:(BBFetchedResultsController *)controller;

- (void)controller:(BBFetchedResultsController *)controller didChangeSection:(id<BBFetchedResultsSectionInfo>)sectionInfo atIndex:(NSUInteger)sectionIndex forChangeType:(BBFetchedResultsChangeType)type;

- (void)controller:(BBFetchedResultsController *)controller didChangeObject:(id)anObject atIndexPath:(BBFetchedResultsIndexPath *)indexPath forChangeType:(BBFetchedResultsChangeType)type newIndexPath:(BBFetchedResultsIndexPath *)newIndexPath;

- (void)controllerDidChangeContent:(BBFetchedResultsController *)controller;

- (NSString *)controller:(BBFetchedResultsController *)controller sectionIndexTitleForSectionName:(NSString *)sectionName;

@end
