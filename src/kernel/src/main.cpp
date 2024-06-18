#include <cstdio>
#include <display.h>
#include <memory>
#include <k_entry.h>
#include <idt.h>
#include <pair>
#include <vector>
#include <scheduling/TaskScheduler.h>

void kernel_main();

extern "C" {
__attribute__((used))
void _start()
{
  kernel_main();
}
}

void kernel_main()
{
  init_idt();
  init_allocator();
  init_task_scheduler();
  std::vector<uint8_t*> test1;
  test1.push_back(new uint8_t(10));
  test1.push_back(new uint8_t(0));
  test1.push_back(new uint8_t(255));
  test1.push_back(new uint8_t(255));
  std::pair<uint8_t, uint8_t> testpair(255, 10);

  auto* test = (color_t*)malloc(sizeof(color_t));
  *test = RGB(*test1[0], *test1[1], testpair.second, testpair.second);

  fill_frame_buffer(*test);
  free(test);
  printf("Pointer: %p", test);

  KERNEL_LOOP_END
}
