
#import "LettersViewController.h"
#import "LettersApp.h"
#import "ResourceManager.h"
#import "Application.h"


@interface LettersViewController () {
  letters::LettersApp letters;
  letters::ResourceManager res;
  ewok::Application app;
}
@property (strong, nonatomic) EAGLContext *context;

@end



@implementation LettersViewController

@synthesize context = _context;


- (void)dealloc
{
    [_context release];x
    [super dealloc];
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
  self.preferredFramesPerSecond = 60.0f;

  [EAGLContext setCurrentContext:self.context];
  
  app.init(letters, res);
}


- (void)viewDidUnload
{    
    [super viewDidUnload];
    
    [EAGLContext setCurrentContext:self.context];
  
    app.deinit();
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc. that aren't in use.
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}


- (void)update
{
  app.update(self.timeSinceLastUpdate);
}


- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
  app.render();
}


- (CGPoint)convertTouchCoordinates:(CGPoint)p
{
  // convert coordinates in landscape mode to:
  // -1 <= x <= 1 and 1 >= y >= -1
  const float rangeX = 1.0f / 480.0f;
  const float rangeY = 1.0f / 320.0f;
  CGPoint r = {p.x * rangeX - 1, (p.y * rangeY - 1) * -1};
  return r;
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
  LogInfo << "touchesBegan count: " << [touches count];
  UITouch *touch = [touches anyObject];
  CGPoint p = [touch locationInView: self.view];
  CGPoint pn = [self convertTouchCoordinates: p];
  app.touchBegin(ewok::Touch(pn.x, pn.y));
}


- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
}


- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
  LogInfo << "touchesEnded count: " << [touches count];
  UITouch *touch = [touches anyObject];
  CGPoint p = [touch locationInView: self.view];
  CGPoint pn = [self convertTouchCoordinates: p];
  app.touchEnd(ewok::Touch(pn.x, pn.y));
}


- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
  LogInfo << "touchesCancelled";
}



@end
