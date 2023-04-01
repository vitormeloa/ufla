import { Router } from 'express';
import tasks from '@/app/schemas/tasks';

const router = new Router();

//getTasks
router.get('/tasks', (req, res) => {
  tasks
    .find()
    .then((data) => {
      const tasks = data.map((task) => {
        return {
          description: task.description,
          deadline: task.deadline,
          complete: task.complete,
        };
      });
      res.send(tasks);
    })
    .catch((error) => {
      console.error('Error trying to get all tasks from the database', error);
      res.status(400).send({
        error: "It wasn't possible to get all tasks. Please, try again!",
      });
    });
});

//getTaskById
router.get('/tasks/:taskId', (req, res) => {
  tasks
    .findOne({ _id: req.params.taskId })
    .then((task) => {
      res.send(task);
    })
    .catch((error) => {
      console.error('Error trying to get task from the database', error);
      res.status(400).send({
        error: "It wasn't possible to get task. Please, try again!",
      });
    });
});

//createTask
router.post('/tasks', (req, res) => {
  const { description, deadline, complete } = req.body;

  tasks
    .create({ description, deadline, complete })
    .then((task) => {
      res.status(200).send(task);
    })
    .catch((error) => {
      console.error('Error trying to save new task to database', error);
      res.status(400).send({
        error:
          "It wasn't possible to save your task. Please, verify your data and try again!",
      });
    });
});

//updateTaskById
router.put('/tasks/:taskId', (req, res) => {
  const { description, deadline, complete } = req.body;

  tasks
    .findByIdAndUpdate(
      req.params.taskId,
      { description, deadline, complete },
      { new: true },
    )
    .then((task) => {
      res.status(200).send(task);
    })
    .catch((error) => {
      console.error('Error trying to update task in database', error);
      res.status(400).send({
        error:
          "It wasn't possible to update your task. Please, verify your data and try again!",
      });
    });
});

//deleteTaskById
router.delete('/tasks/:taskId', (req, res) => {
  tasks
    .findByIdAndRemove(req.params.taskId)
    .then(() => {
      res.send({ message: 'task removed successfully!' });
    })
    .catch((error) => {
      console.error('Error removing task from database.', error);
      res.status(400).send({
        message: 'Error removing task from database. Please, try again!',
      });
    });
});

export default router;
