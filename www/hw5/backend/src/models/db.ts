import mysql from 'mysql2';
import * as dotenv from 'dotenv';
dotenv.config();

const dbOptions = {
    host: process.env.SQL_HOST || 'localhost',
    port: parseInt(process.env.SQL_PORT || '3306'),
    user: process.env.SQL_USER,
    password: process.env.SQL_PASSWORD,
    database: process.env.SQL_DATABASE
};
console.log(dbOptions);
const connection = mysql.createPool(dbOptions);

export default connection;
