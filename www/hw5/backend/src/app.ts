import express from 'express';
import {router} from "./routes/router";
import session from 'express-session';
import sessionStore from './models/sessionStore';

const app: express.Application = express();
const port : number = 12312;

app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(session({
    secret: '48763',
    store: sessionStore,
    resave: false,
    saveUninitialized: false,
    cookie: {
        maxAge: 1000 * 60 * 1 // 1 hour
    }
}));

// load router
for (const route of router) {
  app.use(route.getPrefix(), route.getRouter());
}

app.listen(port, () => {
  console.log(`Server started at http://localhost:${port}`);
});

module.exports = app;
