import mongoose from '@/database';

const tasksSchema = new mongoose.Schema({
  description: {
    type: String,
    required: true,
  },
  deadline: {
    type: Date,
    required: true,
  },
  complete: {
    type: Boolean,
    default: false,
  },
});

export default mongoose.model('tasks', tasksSchema);
