import { Request, Response, NextFunction } from "express";
import DB from "../models/db";

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
  }
  register(req: Request, res: Response, next: NextFunction){
    const { username, password, email } = req.body;
    DB.query('select * from users where email = ?', [email], (err, results) => {
      if (err) {
        console.log(err);
        res.status(500).send('Error registering user');
      } else {
        console.log('Registering user');
        res.send('User registered');
      }
    })
  }
}

export default AuthController;
