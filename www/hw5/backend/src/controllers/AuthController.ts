import { Request, Response, NextFunction } from "express";
import DB from "../models/db";
import mysql from 'mysql2';
import bcrypt from 'bcryptjs';
import googleOAuth2Client from '../config/GoogleOauth2Client';

const SCOPES = [
  'https://mail.google.com/',
];

class AuthController {
  echo(request: Request, response: Response, next: NextFunction) {
    response.type('text/plain');
    response.send('echo');
  }  
  mail_login(req: Request, res: Response, next: NextFunction){
    const { email, password } = req.body;
    console.log(email, password);
    DB.query('select * from users', (err, results: mysql.RowDataPacket[]) => {
      console.log(results)
    });
    DB.query('select * from users where email = ?', [email], (err, results: mysql.RowDataPacket[]) => {
      if (err) {
        console.log(err);
        res.status(500).send('Error logging in');
      } else {
        if(results.length > 0){
          // check password
          if(!bcrypt.compareSync(password, results[0].password_hash)){
            res.status(400).send('Invalid email or password');
          }
          else if(results[0].is_email_verified === 0){
            res.status(400).send('Email not verified');
          }
          else{
            const session : any = req.session;
            session.user_id = results[0].id;
            res.status(200).send('Logged in');
          }
        }
        else {
          res.status(400).send('Invalid email or password');
        }
      }
    
    });
  }
  register(req: Request, res: Response, next: NextFunction){
    const { username, password, email } = req.body;
    console.log('Registering user')
    console.log(username, password, email)
    DB.query('select email, is_email_verified from users where email = ?', [email], (err, results: mysql.RowDataPacket[]) => {
      if (err) {
        console.log(err);
        res.status(500).send('Error registering user');
      } else {
        const nums = results.length;
        if(results.length > 0){
          if (results[0].is_email_verified === 0) {
            res.status(400).send('Email not verified');
          }
          else {
            res.status(400).send('Email already registered');
          }
        }
        else {
          const hash_password = bcrypt.hashSync(password, 8);
          DB.query('insert into users (username, email, password_hash, login_method) values (?, ?, ?, ?)', [username, email, hash_password, 1], (err) => {
            if (err) {
              console.log(err);
              res.status(500).send('Error registering user');
            } else {
              res.status(201).send('User registered');
            }
          });
        }
      }
    })
  }
  google_login(req: Request, res: Response, next: NextFunction){
    const authUrl = googleOAuth2Client.generateAuthUrl({
      access_type: 'offline',
      scope: SCOPES,
    });
    res.redirect(authUrl);
  }
  async google_callback(req: Request, res: Response, next: NextFunction) {
    const code: string = req.query.code as string;
    try {
      const { tokens } = await googleOAuth2Client.getToken(code);
      googleOAuth2Client.setCredentials(tokens);
      const session: any = req.session;
      session.tokens = tokens;
      res.redirect('/email/user');
    } catch (err) {
      console.error('Error authenticating with Google:', err);
      res.status(500).send('Error authenticating with Google');
    }
  }
}

export default AuthController;
