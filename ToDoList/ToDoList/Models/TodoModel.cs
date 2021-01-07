using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ToDoList.Models
{
    class TodoModel
    {
        public DateTime CreationDate { get; set; } = DateTime.Now;

        private bool _isDone;

        public bool IsDone
        {
            get { return _isDone; }
            set { _isDone = value; }
        }

        private string _notes;

        public string _Notes
        {
            get { return _notes; }
            set { _notes = value; }
        }
    }
}
