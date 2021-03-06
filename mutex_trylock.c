#include <linux/mutex.h>	         /// Required for the mutex functionality
…
static DEFINE_MUTEX(ebbchar_mutex);  /// A macro that is used to declare a new mutex that is visible in this file
                                     /// results in a semaphore variable ebbchar_mutex with value 1 (unlocked)
                                     /// DEFINE_MUTEX_LOCKED() results in a variable with value 0 (locked)
…
static int __init ebbchar_init(void){
   …
   mutex_init(&ebbchar_mutex);       /// Initialize the mutex lock dynamically at runtime
}
 
static int dev_open(struct inode *inodep, struct file *filep){
   if(!mutex_trylock(&ebbchar_mutex)){    /// Try to acquire the mutex (i.e., put the lock on/down)
                                          /// returns 1 if successful and 0 if there is contention
      printk(KERN_ALERT "EBBChar: Device in use by another process");
      return -EBUSY;
   }
   …
}
 
static int dev_release(struct inode *inodep, struct file *filep){
   mutex_unlock(&ebbchar_mutex);          /// Releases the mutex (i.e., the lock goes up)
   …
}
 
static void __exit ebbchar_exit(void){
   mutex_destroy(&ebbchar_mutex);        /// destroy the dynamically-allocated mutex
   …
}
