/*
 * This file is part of UbuntuOne Qt Files.
 *
 * UbuntuOne Qt Files is free software:  you can redistribute it  and/or  modify it under the terms of the  GNU  General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * UbuntuOne Qt Files  is distributed in the hope  that it will be useful,  but  WITHOUT ANY WARRANTY;  without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include "iOSFileOpener.h"

#include <QtCore>
#ifdef Q_OS_IOS

@interface iOSFileOpener ()
    @property (nonatomic) bool visible;
    @property (nonatomic, strong) UIViewController *viewController;
    @property (nonatomic, strong) UIDocumentInteractionController *documentInteractionController;
@end

@implementation iOSFileOpener

+ (iOSFileOpener *)getInstance
{
    static dispatch_once_t pred;
    static iOSFileOpener *instance = nil;

    dispatch_once(&pred, ^{
        instance = [[iOSFileOpener alloc] init];
    });
    return instance;
}

- (id)init
{
    self = [super init];
    if(!self)
        return nil;

    self.visible = false;
    self.documentInteractionController = [[UIDocumentInteractionController alloc] init];
    [self.documentInteractionController setDelegate:self];

    return self;
}

- (void)openFile:(NSString *)path fromViewController:(UIViewController *)viewController
{
    if (self.visible)
        return;

    self.visible = true;
    self.viewController = viewController;
    NSURL *urlPath = [NSURL URLWithString:[path stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    self.documentInteractionController.URL = urlPath;
    [self.documentInteractionController presentPreviewAnimated:YES];
}

- (UIViewController *)documentInteractionControllerViewControllerForPreview:(UIDocumentInteractionController *)controller
{
    Q_UNUSED(controller);
    return self.viewController;
}

- (void)documentInteractionControllerDidEndPreview:(UIDocumentInteractionController *)controller
{
    Q_UNUSED(controller);
    self.visible = false;

}

@end

#endif // Q_OS_IOS
