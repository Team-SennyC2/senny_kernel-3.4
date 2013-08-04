#ifndef _LINUX_VMSTAT_H
#define _LINUX_VMSTAT_H

#include <linux/types.h>
#include <linux/percpu.h>
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/vm_event_item.h>
#include <linux/atomic.h>

extern int sysctl_stat_interval;

#ifdef CONFIG_VM_EVENT_COUNTERS

struct vm_event_state {
	unsigned long event[NR_VM_EVENT_ITEMS];
};

DECLARE_PER_CPU(struct vm_event_state, vm_event_states);

static inline void __count_vm_event(enum vm_event_item item)
{
	__this_cpu_inc(vm_event_states.event[item]);
}

static inline void count_vm_event(enum vm_event_item item)
{
	this_cpu_inc(vm_event_states.event[item]);
}

static inline void __count_vm_events(enum vm_event_item item, long delta)
{
	__this_cpu_add(vm_event_states.event[item], delta);
}

static inline void count_vm_events(enum vm_event_item item, long delta)
{
	this_cpu_add(vm_event_states.event[item], delta);
}

extern void all_vm_events(unsigned long *);
#ifdef CONFIG_HOTPLUG
extern void vm_events_fold_cpu(int cpu);
#else
static inline void vm_events_fold_cpu(int cpu)
{
}
#endif

#else

static inline void count_vm_event(enum vm_event_item item)
{
}
static inline void count_vm_events(enum vm_event_item item, long delta)
{
}
static inline void __count_vm_event(enum vm_event_item item)
{
}
static inline void __count_vm_events(enum vm_event_item item, long delta)
{
}
static inline void all_vm_events(unsigned long *ret)
{
}
static inline void vm_events_fold_cpu(int cpu)
{
}

#endif 

#define __count_zone_vm_events(item, zone, delta) \
		__count_vm_events(item##_NORMAL - ZONE_NORMAL + \
		zone_idx(zone), delta)

extern atomic_long_t vm_stat[NR_VM_ZONE_STAT_ITEMS];

static inline void zone_page_state_add(long x, struct zone *zone,
				 enum zone_stat_item item)
{
	atomic_long_add(x, &zone->vm_stat[item]);
	atomic_long_add(x, &vm_stat[item]);
}

static inline unsigned long global_page_state(enum zone_stat_item item)
{
	long x = atomic_long_read(&vm_stat[item]);
#ifdef CONFIG_SMP
	if (x < 0)
		x = 0;
#endif
	return x;
}

static inline unsigned long zone_page_state(struct zone *zone,
					enum zone_stat_item item)
{
	long x = atomic_long_read(&zone->vm_stat[item]);
#ifdef CONFIG_SMP
	if (x < 0)
		x = 0;
#endif
	return x;
}

static inline unsigned long zone_page_state_snapshot(struct zone *zone,
					enum zone_stat_item item)
{
	long x = atomic_long_read(&zone->vm_stat[item]);

#ifdef CONFIG_SMP
	int cpu;
	for_each_online_cpu(cpu)
		x += per_cpu_ptr(zone->pageset, cpu)->vm_stat_diff[item];

	if (x < 0)
		x = 0;
#endif
	return x;
}

extern unsigned long global_reclaimable_pages(void);
extern unsigned long zone_reclaimable_pages(struct zone *zone);

#ifdef CONFIG_NUMA
static inline unsigned long node_page_state(int node,
				 enum zone_stat_item item)
{
	struct zone *zones = NODE_DATA(node)->node_zones;

	return
#ifdef CONFIG_ZONE_DMA
		zone_page_state(&zones[ZONE_DMA], item) +
#endif
#ifdef CONFIG_ZONE_DMA32
		zone_page_state(&zones[ZONE_DMA32], item) +
#endif
#ifdef CONFIG_HIGHMEM
		zone_page_state(&zones[ZONE_HIGHMEM], item) +
#endif
		zone_page_state(&zones[ZONE_NORMAL], item) +
		zone_page_state(&zones[ZONE_MOVABLE], item);
}

extern void zone_statistics(struct zone *, struct zone *, gfp_t gfp);

#else

#define node_page_state(node, item) global_page_state(item)
#define zone_statistics(_zl, _z, gfp) do { } while (0)

#endif 

#define add_zone_page_state(__z, __i, __d) mod_zone_page_state(__z, __i, __d)
#define sub_zone_page_state(__z, __i, __d) mod_zone_page_state(__z, __i, -(__d))

static inline void zap_zone_vm_stats(struct zone *zone)
{
	memset(zone->vm_stat, 0, sizeof(zone->vm_stat));
}

extern void inc_zone_state(struct zone *, enum zone_stat_item);

#ifdef CONFIG_SMP
void __mod_zone_page_state(struct zone *, enum zone_stat_item item, int);
void __inc_zone_page_state(struct page *, enum zone_stat_item);
void __dec_zone_page_state(struct page *, enum zone_stat_item);

void mod_zone_page_state(struct zone *, enum zone_stat_item, int);
void inc_zone_page_state(struct page *, enum zone_stat_item);
void dec_zone_page_state(struct page *, enum zone_stat_item);

extern void inc_zone_state(struct zone *, enum zone_stat_item);
extern void __inc_zone_state(struct zone *, enum zone_stat_item);
extern void dec_zone_state(struct zone *, enum zone_stat_item);
extern void __dec_zone_state(struct zone *, enum zone_stat_item);

void refresh_cpu_vm_stats(int);
void refresh_zone_stat_thresholds(void);

int calculate_pressure_threshold(struct zone *zone);
int calculate_normal_threshold(struct zone *zone);
void set_pgdat_percpu_threshold(pg_data_t *pgdat,
				int (*calculate_pressure)(struct zone *));
#else 

static inline void __mod_zone_page_state(struct zone *zone,
			enum zone_stat_item item, int delta)
{
	zone_page_state_add(delta, zone, item);
}

static inline void __inc_zone_state(struct zone *zone, enum zone_stat_item item)
{
	atomic_long_inc(&zone->vm_stat[item]);
	atomic_long_inc(&vm_stat[item]);
}

static inline void __inc_zone_page_state(struct page *page,
			enum zone_stat_item item)
{
	__inc_zone_state(page_zone(page), item);
}

static inline void __dec_zone_state(struct zone *zone, enum zone_stat_item item)
{
	atomic_long_dec(&zone->vm_stat[item]);
	atomic_long_dec(&vm_stat[item]);
}

static inline void __dec_zone_page_state(struct page *page,
			enum zone_stat_item item)
{
	__dec_zone_state(page_zone(page), item);
}

#define inc_zone_page_state __inc_zone_page_state
#define dec_zone_page_state __dec_zone_page_state
#define mod_zone_page_state __mod_zone_page_state

#define set_pgdat_percpu_threshold(pgdat, callback) { }

static inline void refresh_cpu_vm_stats(int cpu) { }
static inline void refresh_zone_stat_thresholds(void) { }

#endif		

extern const char * const vmstat_text[];

#endif 