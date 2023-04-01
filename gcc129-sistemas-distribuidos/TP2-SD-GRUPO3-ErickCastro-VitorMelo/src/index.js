import express from 'express';
import bodyParser from 'body-parser';
import { tasks } from '@/app/controllers';

const app = express();
const port = 3000;

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.use('/', tasks);

console.log(`Server running on the link http://localhost:${port}`);
app.listen(port);
