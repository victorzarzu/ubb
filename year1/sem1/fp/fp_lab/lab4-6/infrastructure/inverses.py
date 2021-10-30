import domain.participants as participants

def inverse_of_the_function(function):
  """
  function that returns the inverse of the operation function
  params: operation - a function
  return: a function
  """
  if function == participants.add_participant_in_list:
    return participants.remove_participant_from_list
  elif function in [participants.insert_score_by_participant_id, participants.delete_participant_score_by_id, participants.replace_participant_score_by_id, participants.filter_participants_by_comparer]:
    return participants.replace_participant_score_by_id

def inverse_of_the_function_test():
  inverse = inverse_of_the_function(participants.add_participant_in_list)
  assert inverse == participants.remove_participant_from_list

  inverse = inverse_of_the_function(participants.filter_participants_by_comparer)
  assert inverse == participants.replace_participant_score_by_id

  inverse = inverse_of_the_function(participants.delete_participant_score_by_id)
  assert inverse == participants.replace_participant_score_by_id

inverse_of_the_function_test()
