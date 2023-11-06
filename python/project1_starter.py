from datetime import datetime, timedelta

def parse_time(time_str):
    return datetime.strptime(time_str, '%H:%M')

def format_time(time_obj):
    return time_obj.strftime('%H:%M')

def find_free_slots(schedule, daily_act, duration):
    free_slots = []
    start_time = parse_time(daily_act[0])
    end_time = parse_time(daily_act[1])

    current_time = start_time
    for event in schedule:
        event_start, event_end = parse_time(event[0]), parse_time(event[1])
        if current_time < event_start:
            free_duration = event_start - current_time
            if free_duration >= timedelta(minutes=duration):
                free_slots.append([format_time(current_time), format_time(event_start)])
        current_time = max(current_time, event_end)

    if current_time < end_time:
        free_duration = end_time - current_time
        if free_duration >= timedelta(minutes=duration):
            free_slots.append([format_time(current_time), format_time(end_time)])

    return free_slots

def group_schedule_matching(person1_schedule, person1_daily_act, person2_schedule, person2_daily_act, duration_of_meeting):
    person1_free_slots = find_free_slots(person1_schedule, person1_daily_act, duration_of_meeting)
    person2_free_slots = find_free_slots(person2_schedule, person2_daily_act, duration_of_meeting)

    common_free_slots = []
    i, j = 0, 0

    while i < len(person1_free_slots) and j < len(person2_free_slots):
        start_time1, end_time1 = parse_time(person1_free_slots[i][0]), parse_time(person1_free_slots[i][1])
        start_time2, end_time2 = parse_time(person2_free_slots[j][0]), parse_time(person2_free_slots[j][1])

        overlap_start = max(start_time1, start_time2)
        overlap_end = min(end_time1, end_time2)

        if overlap_start < overlap_end:
            common_free_slots.append([format_time(overlap_start), format_time(overlap_end)])

        if end_time1 < end_time2:
            i += 1
        else:
            j += 1

    return common_free_slots

person1_schedule = [['7:00', '8:30'], ['12:00', '13:00'], ['16:00', '18:00']]
person1_daily_act = ['9:00', '19:00']
person2_schedule = [['9:00', '10:30'], ['12:20', '13:30'], ['14:00', '15:00'], ['16:00', '17:00']]
person2_daily_act = ['9:00', '18:30']
duration_of_meeting = 30

result = group_schedule_matching(person1_schedule, person1_daily_act, person2_schedule, person2_daily_act, duration_of_meeting)
print(result)
