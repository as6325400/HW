import { Request, Response, NextFunction } from "express";

class AuthController {
  echo(request: Request, response: Response, next: NextFunction) {
    response.type('text/plain');
    response.send('echo');
  }  
  test(req: Request, res: Response, next: NextFunction){
    const session : any = req.session;
    if (session.views) {
        session.views++;
        res.send(`<p>Number of views: ${session.views}</p>`);
    } else {
        session.views = 1;
        res.send('Welcome to the session demo. Refresh!');
    }
  };
}

export default AuthController;
