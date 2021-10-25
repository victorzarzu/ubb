import participants, comparators
from computes import compute_average
from conversions import convert_id_interval
from validations import validate_participant_id_interval

def add_element_in_list(score_l, score):
    """
  function that adds score in score_l list
  params: score_l - a list of floats; score - a float
  return: -
  """
    score_l.append(score)


def create_participant_score_avg_list_by_interval(par_l, id_interval):
    """
  function that returns a list with the score averages of all participants
  params: par_l - a list of participant items; id_interval - a list of 2 integers
  return: a list of floats
  """
    average_list = []
    for i in range(id_interval[0], id_interval[1] + 1):
        participant_score_avg = participants.get_participant_score_avg(par_l[i])
        add_element_in_list(average_list, participant_score_avg)
    else:
        return average_list


def svg_participants_average_by_id_interval(par_l, id_interval):
    """
  function that computes the average of the average scores of all participants in the inverval
  params: par_l - a list of participant items; interval - a string
  return: a float representing the average of the average scores of the participants in the given interval
  """
    id_interval = convert_id_interval(id_interval)
    validate_participant_id_interval(par_l, id_interval)
    average_list = create_participant_score_avg_list_by_interval(par_l, id_interval)
    average = compute_average(average_list)
    return average


def minimum_score_by_interval(par_l, id_interval):
    """
  function that returns the minimum average score of a participant in a given interval of ids
  params: par_l - a list of participant items; interval - a list of 2 intergers
  return: a float
  """
    minimum = 11
    for i in range(id_interval[0], id_interval[1] + 1):
        participant_average_score = participants.get_participant_score_avg(par_l[i])
        if comparators.comparer_smaller(participant_average_score, minimum):
            minimum = participant_average_score
    else:
        return minimum


def svg_minimum_score_by_interval(par_l, id_interval):
    """
  function that computes the minimum of the average scores of all participants in the inverval
  params: par_l - a list of participant items; interval - a string
  return: a float representing the minimum of the average scores of the participants in the given interval
  """
    id_interval = convert_id_interval(id_interval)
    validate_participant_id_interval(par_l, id_interval)
    minimum = minimum_score_by_interval(par_l, id_interval)
    return minimum


def create_participant_id_if_multiple(par_l, id_interval, div):
    """
  function that creates a list of integers that are the ids of the participant that a score a multiple of div
  params: par_l - a list of participant items; id_interval - a list of 2 integers; div: a float value
  """
    id_l = []
    for i in range(id_interval[0], id_interval[1] + 1):
        participant_average_score = participants.get_participant_score_avg(par_l[i])
        participant_score = participants.get_participant_score(par_l[i])
        participant_average_score *= len(participant_score)
        if comparators.comparer_divisible(participant_average_score, div):
            participant_id = participants.get_participant_id(par_l[i])
            add_element_in_list(id_l, participant_id)
    else:
        return id_l


def create_string_ids(id_l):
    """
  creates a string to be shown based on the id_l list
  params: id_l - a list  of intergers
  return: a string
  """
    if not len(id_l):
        return 'no participants!'
    ids = 'ids: '
    for _id in id_l:
        ids += str(_id) + ' '
    else:
        ids = ids[:-1]
        return ids


def svg_participant_ids_if_multiple(par_l, id_interval, div):
    """
  function that computes the ids of the participants that have the score a multiple of div 
  params: par_l - a list of participant items; interval - a string; div - a float
  return: a string 
  """
    id_interval = convert_id_interval(id_interval)
    validate_participant_id_interval(par_l, id_interval)
    id_l = create_participant_id_if_multiple(par_l, id_interval, div)
    ids = create_string_ids(id_l)
    return ids


def ui_operate_score(par_l):
    cmd = input().lstrip().rstrip()
    if cmd == 'avg_int':
        id_interval = input('id interval: ')
        average = svg_participants_average_by_id_interval(par_l, id_interval)
        print('{:.2f}'.format(average))
    elif cmd == 'min_int':
        id_interval = input('id_interval: ')
        minimum = svg_minimum_score_by_interval(par_l, id_interval)
        print('{:.2f}'.format(minimum))
    elif cmd == 'mul_10':
        id_interval = input('id interval: ')
        ids = svg_participant_ids_if_multiple(par_l, id_interval, 10)
        print(ids)
    else:
        print('invalid command!')


def add_element_in_list_test():
    score_l = []
    add_element_in_list(score_l, 6)
    add_element_in_list(score_l, 8)
    add_element_in_list(score_l, 1)
    assert score_l == [6, 8, 1]


def create_participant_score_avg_list_by_interval_test():
    par_l = []
    participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [1, 1, 1, 1], compute_average([1, 1, 1, 1]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
    participants.add_participant_in_list(par_l, participant)
    average_list = create_participant_score_avg_list_by_interval(par_l, [0, 2])
    assert average_list == [compute_average([8, 9, 9]), 1, 7]
    participant = participants.create_participant(len(par_l), [6, 6, 6, 7], compute_average([6, 6, 6, 7]))
    participants.add_participant_in_list(par_l, participant)
    average_list = create_participant_score_avg_list_by_interval(par_l, [1, 3])
    assert average_list == [1, 7, compute_average([6, 6, 6, 7])]


def svg_participants_average_by_id_interval_test():
    par_l = []
    participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [1, 1, 1, 1], compute_average([1, 1, 1, 1]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
    participants.add_participant_in_list(par_l, participant)
    average = svg_participants_average_by_id_interval(par_l, '0 1')
    assert average == compute_average([compute_average([8, 9, 9]), 1])


def minimum_score_by_interval_test():
    par_l = []
    participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [1, 2, 1, 1], compute_average([1, 2, 1, 1]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
    participants.add_participant_in_list(par_l, participant)
    minimum = minimum_score_by_interval(par_l, [0, 2])
    assert minimum == compute_average([1, 2, 1, 1])


def svg_minimum_score_by_interval_test():
    par_l = []
    participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [5, 2, 4, 1], compute_average([5, 2, 4, 1]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
    participants.add_participant_in_list(par_l, participant)
    minimum = svg_minimum_score_by_interval(par_l, '0 2')
    assert minimum == compute_average([5, 2, 4, 1])
    participant = participants.create_participant(len(par_l), [1, 2, 1], compute_average([1, 2, 1]))
    participants.add_participant_in_list(par_l, participant)
    minimum = svg_minimum_score_by_interval(par_l, '0 3')
    assert minimum == compute_average([1, 2, 1])


def create_participant_id_if_multiple_test():
    par_l = []
    participant = participants.create_participant(len(par_l), [1, 2, 7], compute_average([1, 2, 7]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [5, 2, 4, 1], compute_average([5, 2, 4, 1]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
    participants.add_participant_in_list(par_l, participant)
    id_l = create_participant_id_if_multiple(par_l, [0, 2], 10)
    assert id_l == [0]
    participant = participants.create_participant(len(par_l), [5, 7, 7], compute_average([5, 7, 7]))
    participants.add_participant_in_list(par_l, participant)
    id_l = create_participant_id_if_multiple(par_l, [1, 3], 10)
    assert id_l == []


def svg_participant_ids_if_multiple_test():
    par_l = []
    participant = participants.create_participant(len(par_l), [1, 2, 7], compute_average([1, 2, 7]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [5, 2, 4, 1], compute_average([5, 2, 4, 1]))
    participants.add_participant_in_list(par_l, participant)
    participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
    participants.add_participant_in_list(par_l, participant)
    id_l = svg_participant_ids_if_multiple(par_l, '0 2', 10)
    assert id_l == 'ids: 0'
    participant = participants.create_participant(len(par_l), [5, 7, 7], compute_average([5, 7, 7]))
    participants.add_participant_in_list(par_l, participant)
    id_l = svg_participant_ids_if_multiple(par_l, '1 3', 10)
    assert id_l == 'no participants!'


def create_string_ids_test():
    id_l = [
     1, 7, 10, 20]
    ids = create_string_ids(id_l)
    assert ids == 'ids: 1 7 10 20'


add_element_in_list_test()
create_participant_score_avg_list_by_interval_test()
svg_participants_average_by_id_interval_test()
minimum_score_by_interval_test()
svg_minimum_score_by_interval_test()
create_participant_id_if_multiple_test()
svg_participant_ids_if_multiple_test()
create_string_ids_test()
