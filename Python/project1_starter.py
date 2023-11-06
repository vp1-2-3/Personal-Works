def time_to_minutes(time_str):
    hours, minutes = map(int, time_str.split(':'))
    return hours * 60 + minutes

def minutes_to_time(minutes):
    return f'{minutes // 60:02d}:{minutes % 60:02d}'

def find_available_time_slots(schedule, daily_act, duration):
    available_slots = []
    start_time = time_to_minutes(daily_act[0])
    end_time = time_to_minutes(daily_act[1])

    for busy_slot in schedule:
        busy_start = time_to_minutes(busy_slot[0])
        busy_end = time_to_minutes(busy_slot[1])

        if start_time < busy_start:
            available_slots.append([minutes_to_time(start_time), minutes_to_time(busy_start)])

        start_time = busy_end

    if end_time > start_time:
        available_slots.append([minutes_to_time(start_time), minutes_to_time(end_time)])

    return [slot for slot in available_slots if (time_to_minutes(slot[1]) - time_to_minutes(slot[0])) >= duration]

def find_common_time_slots(person1_schedule, person1_daily_act, person2_schedule, person2_daily_act, duration_of_meeting):
    person1_available = find_available_time_slots(person1_schedule, person1_daily_act, duration_of_meeting)
    person2_available = find_available_time_slots(person2_schedule, person2_daily_act, duration_of_meeting)

    common_slots = []
    for slot1 in person1_available:
        for slot2 in person2_available:
            start_time1 = time_to_minutes(slot1[0])
            end_time1 = time_to_minutes(slot1[1])
            start_time2 = time_to_minutes(slot2[0])
            end_time2 = time_to_minutes(slot2[1])

            overlap_start = max(start_time1, start_time2)
            overlap_end = min(end_time1, end_time2)

            if overlap_start < overlap_end and (overlap_end - overlap_start) >= duration_of_meeting:
                common_slots.append([minutes_to_time(overlap_start), minutes_to_time(overlap_end)])

    return common_slots

def main():
    with open('input.txt', 'r') as file:
        input_lines = file.read().split('\n\n')

    with open('output.txt', 'w') as output_file:
        for i, input_data in enumerate(input_lines):
            lines = input_data.strip().split('\n')
            person1_schedule = [line.split() for line in lines[0].split(',')]
            person1_daily_act = lines[1].split()
            person2_schedule = [line.split() for line in lines[2].split(',')]
            person2_daily_act = lines[3].split()
            duration_of_meeting = int(lines[4])

            common_time_slots = find_common_time_slots(person1_schedule, person1_daily_act, person2_schedule, person2_daily_act, duration_of_meeting)

            output_file.write(f"Test Case {i + 1}:\n")
            for slot in common_time_slots:
                output_file.write(f'[{slot[0]} - {slot[1]}] ')
            output_file.write("\n\n")

if __name__ == '__main__':
    main()
