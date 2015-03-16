// Generated by Swift version 1.1 (swift-600.0.54.20)
#pragma clang diagnostic push

#if defined(__has_include) && __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <objc/NSObject.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(__has_include) && __has_include(<uchar.h>)
# include <uchar.h>
#elif !defined(__cplusplus) || __cplusplus < 201103L
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
#endif

typedef struct _NSZone NSZone;

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif

#if defined(__has_attribute) && __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if defined(__has_attribute) && __has_attribute(objc_subclassing_restricted) 
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if defined(__has_attribute) && __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if defined(__has_feature) && __has_feature(modules)
@import UIKit;
@import CoreLocation;
@import CoreGraphics;
@import ObjectiveC;
@import MapKit;
#endif

#import "/Users/brandondougherty/Documents/Grubber/Grubber/Grubber-Bridging-Header.h"

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
@class UIWindow;
@class UINavigationController;
@class UIApplication;
@class NSObject;
@class NSURL;
@class NSManagedObjectModel;
@class NSPersistentStoreCoordinator;
@class NSManagedObjectContext;

SWIFT_CLASS("_TtC7Grubber11AppDelegate")
@interface AppDelegate : UIResponder <UIApplicationDelegate>
@property (nonatomic) UIWindow * window;
@property (nonatomic) UINavigationController * NavigationController;
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
- (void)applicationWillResignActive:(UIApplication *)application;
- (void)applicationDidEnterBackground:(UIApplication *)application;
- (void)applicationWillEnterForeground:(UIApplication *)application;
- (void)applicationDidBecomeActive:(UIApplication *)application;
- (void)applicationWillTerminate:(UIApplication *)application;
@property (nonatomic) NSURL * applicationDocumentsDirectory;
@property (nonatomic) NSManagedObjectModel * managedObjectModel;
@property (nonatomic) NSPersistentStoreCoordinator * persistentStoreCoordinator;
@property (nonatomic) NSManagedObjectContext * managedObjectContext;
- (void)saveContext;
- (instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end

@class NSBundle;
@class NSCoder;

SWIFT_CLASS("_TtC7Grubber26CellSelectedViewController")
@interface CellSelectedViewController : UIViewController
- (void)viewDidLoad;
- (void)didReceiveMemoryWarning;
- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil OBJC_DESIGNATED_INITIALIZER;
- (instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder OBJC_DESIGNATED_INITIALIZER;
@end

@class UIButton;
@class NSString;
@class CLLocationManager;
@class UILabel;
@class UISlider;

SWIFT_CLASS("_TtC7Grubber19FrontViewController")
@interface FrontViewController : UIViewController <CLLocationManagerDelegate>
@property (nonatomic) UIButton * button;
@property (nonatomic) BOOL seenError;
@property (nonatomic) BOOL locationFixAchieved;
@property (nonatomic) NSString * locationStatus;
@property (nonatomic) CLLocationManager * locationManager;
@property (nonatomic) IBOutlet UILabel * sliderDisplayLabel;
- (void)viewDidLoad;
- (void)sliderValueDidChange:(UISlider *)sender;
- (CGRect)trackRectForBounds:(CGRect)bounds;
- (void)initLocationManager;
- (void)foodAction:(UIButton *)sender;
- (void)barAction:(UIButton *)sender;
- (void)didReceiveMemoryWarning;
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status;
- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil OBJC_DESIGNATED_INITIALIZER;
- (instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC7Grubber6MapPin")
@interface MapPin : NSObject <MKAnnotation>
@property (nonatomic) CLLocationCoordinate2D coordinate;
@property (nonatomic, copy) NSString * title;
@property (nonatomic, copy) NSString * subtitle;
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate title:(NSString *)title subtitle:(NSString *)subtitle OBJC_DESIGNATED_INITIALIZER;
@end

@class GMSMapView;

SWIFT_CLASS("_TtC7Grubber17MapViewController")
@interface MapViewController : UIViewController <GMSMapViewDelegate>
@property (nonatomic) GMSMapView * gmaps;
- (void)viewDidLoad;
- (void)didReceiveMemoryWarning;
- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil OBJC_DESIGNATED_INITIALIZER;
- (instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder OBJC_DESIGNATED_INITIALIZER;
@end


SWIFT_CLASS("_TtC7Grubber6Marker")
@interface Marker : NSObject
- (instancetype)initWithId:(NSString *)id marker:(MapPin *)marker OBJC_DESIGNATED_INITIALIZER;
@end

@class UIImageView;

SWIFT_CLASS("_TtC7Grubber13TableViewCell")
@interface TableViewCell : UITableViewCell
@property (nonatomic, weak) IBOutlet UILabel * locationName;
@property (nonatomic, weak) IBOutlet UILabel * locationOpen;
@property (nonatomic, weak) IBOutlet UIImageView * locationOpenImg;
@property (nonatomic, weak) IBOutlet UILabel * vicinity;
@property (nonatomic, weak) IBOutlet UILabel * minutesOpen;
@property (nonatomic, weak) IBOutlet UILabel * listNumber;
@property (nonatomic, weak) IBOutlet UIImageView * numberIconBackground;
- (void)awakeFromNib;
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;
- (void)loadItemWithName:(NSString *)name open:(NSInteger)open location:(NSString *)location timeLeft:(NSInteger)timeLeft;
- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier OBJC_DESIGNATED_INITIALIZER;
- (instancetype)initWithFrame:(CGRect)frame OBJC_DESIGNATED_INITIALIZER;
- (instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder OBJC_DESIGNATED_INITIALIZER;
@end

@class MKMapView;
@class NSArray;
@class UIRefreshControl;
@class NSIndexPath;
@class NSMutableDictionary;
@class UITableView;
@class UIView;
@class UISnapBehavior;
@class UIDynamicAnimator;
@class UIAttachmentBehavior;
@class UIGravityBehavior;
@class UICollisionBehavior;
@class UIBarButtonItem;
@class NSError;

SWIFT_CLASS("_TtC7Grubber19TableViewController")
@interface TableViewController : UIViewController <CLLocationManagerDelegate, UITableViewDelegate, UITableViewDataSource, GMSMapViewDelegate, MKMapViewDelegate>
@property (nonatomic, readonly) NSInteger RADIUS;
@property (nonatomic, readonly, copy) NSString * APIKey;
@property (nonatomic) MKMapView * mapView;
@property (nonatomic, copy) NSArray * markers;
@property (nonatomic) BOOL seenError;
@property (nonatomic) BOOL locationFixAchieved;
@property (nonatomic) NSString * locationStatus;
@property (nonatomic) CLLocationManager * locationManager;
@property (nonatomic) NSArray * types;
@property (nonatomic, copy) NSString * name;
@property (nonatomic, copy) NSString * vicinity;
@property (nonatomic) UIRefreshControl * refreshControler;
@property (nonatomic) NSIndexPath * selectedRowIndex;
@property (nonatomic) NSMutableDictionary * imageCache;
@property (nonatomic) UITableView * tableView;
@property (nonatomic) UIView * tempView;
@property (nonatomic) GMSMapView * gmaps;
@property (nonatomic) UIButton * button;
@property (nonatomic) UISnapBehavior * snap;
@property (nonatomic) UIDynamicAnimator * animator;
@property (nonatomic) UIAttachmentBehavior * attachmentBehavior;
@property (nonatomic) UISnapBehavior * snapBehavior;
@property (nonatomic) UISnapBehavior * snapBehavior1;
@property (nonatomic) UIDynamicAnimator * animator1;
@property (nonatomic) UIGravityBehavior * gravity;
@property (nonatomic) UICollisionBehavior * collision;
- (void)viewDidLoad;
- (void)popToRoot:(UIBarButtonItem *)sender;
- (void)buttonAction:(UIButton *)sender;
- (void)returnAction:(UIButton *)sender;
- (void)animateMapPanelYPositionYWithTargetPosition:(CGFloat)targetPosition completion:(void (^)(BOOL))completion;
- (void)refresh:(id)sender;
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section;
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)initLocationManager;
- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error;
- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations;
- (NSInteger)minutesUntilClose:(NSInteger)close hour:(NSInteger)hour minute:(NSInteger)minute;
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status;
- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil OBJC_DESIGNATED_INITIALIZER;
- (instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder OBJC_DESIGNATED_INITIALIZER;
@end

#pragma clang diagnostic pop
