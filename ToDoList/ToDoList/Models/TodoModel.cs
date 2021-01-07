using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ToDoList.Models
{
    class TodoModel
    {

        private bool _isDone;
        private string _notes;

        public DateTime CreationDate { get; set; } = DateTime.Now;

        public bool IsDone
        {
            get { return _isDone; }
            set { _isDone = value; }
        }

        public string Notes
        {
            get { return _notes; }
            set { _notes = value; }
        }
    }
}
