/*timer.c*/

void timer_sleep (int64_t ticks) 
{
  int64_t start = timer_ticks ();
  
  ASSERT (intr_get_level () == INTR_ON);
  //while (timer_elapsed (start) < ticks) 
    //thread_yield ();

    /*Start*/
    thread_sleep(start + ticks); // Adicionei isso na linha 99
    /*End*/
}

static void
timer_interrupt (struct intr_frame *args UNUSED)
{
  ticks++;
  thread_tick ();
  /*Start*/
  wake_up_thread(ticks); // Adicionei isso na linha 181
  /*End*/
}

/*thread.h*/

struct thread
  {
    /* Owned by thread.c. */
    tid_t tid;                          /* Thread identifier. */
    enum thread_status status;          /* Thread state. */
    char name[16];                      /* Name (for debugging purposes). */
    uint8_t *stack;                     /* Saved stack pointer. */
    int priority;                       /* Priority. */
    struct list_elem allelem;           /* List element for all threads list. */

    /* Shared between thread.c and synch.c. */
    struct list_elem elem;              /* List element. */

    /*Start*/
   int64_t wake_up; // Adicionei isso na linha 98
   /*End*/

#ifdef USERPROG
    /* Owned by userprog/process.c. */
    uint32_t *pagedir;                  /* Page directory. */
#endif

    /* Owned by thread.c. */
    unsigned magic;                     /* Detects stack overflow. */
  };

/*Start*/
typedef struct thread Thread; // Adicionei isso na linha 111
/*End*/

/*Start*/
void thread_sleep(int64_t ticks); // Adicionei isso na linha 151
void wake_up_thread(int64_t); //Adicionei isso na linha 152
/*End*/

/*thread.c*/

/*Start*/
static struct list blocked_list; // Adicionei isso na linha 32
/*End*/

void thread_init (void) 
{
  ASSERT (intr_get_level () == INTR_OFF);

  lock_init (&tid_lock);
  list_init (&ready_list);
  list_init (&all_list);

  /*Start*/
  list_init(&blocked_list); // Adicionei isso na linha 102
  /*End*/

  /* Set up a thread structure for the running thread. */
  initial_thread = running_thread ();
  init_thread (initial_thread, "main", PRI_DEFAULT);
  initial_thread->status = THREAD_RUNNING;
  initial_thread->tid = allocate_tid ();
}

// Adicionei as seguintes funções da linha 16o até a linha 194
/*Start*/
void thread_sleep(int64_t ticks)
{
  //struct thread *current = thread_current();
  Thread *current = thread_current();
  enum intr_level old_level;

  old_level = intr_disable(); 

  ASSERT(current != idle_thread); 

  current->wake_up = ticks;

  list_push_back(&blocked_list, &current->elem);
  thread_block();

  intr_set_level(old_level);
}

void wake_up_thread(int64_t ticks)
{
  struct list_elem *current_element;
  struct list_elem *next_element;

  for (current_element = list_begin(&blocked_list); current_element != list_end(&blocked_list); current_element = next_element)
  {
    Thread *th = list_entry(current_element, struct thread, elem);
    next_element = list_next(current_element);

    if (th->wake_up <= ticks)
    {
      list_remove(current_element);
      thread_unblock(th);
    }
  }
}
/*End*/