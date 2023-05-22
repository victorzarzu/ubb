$(function() {
  $(".sortableTable").tablesorter({});
});


$('.horizontalSortableTable th').click(function(){
  var table = $(this).parents('table').eq(0)
  var rows = table.find('tr').toArray();
  index = $(this).parent().index();
  parentRow = $(this).parent();
  indexes = [];
  for(let i = 0;i < parentRow.children('td').length;i++) {
    indexes.push(i);
  }

  indexes = indexes.sort(horizontalComparer(parentRow));

  for(row of rows) {
    texts = [];
    for(let i = 0;i < parentRow.children('td').length;i++) {
      texts.push($(row).children('td').eq(indexes[i]).text());
    }

    for(let i = 0;i < parentRow.children('td').length;i++) {
      $(row).children('td').eq(i).text(texts[i]);
    }
  }
  for (var i = 0; i < rows.length; i++){
    $(rows[i]).detach();
  }

  for (var i = 0; i < rows.length; i++){
    table.append(rows[i]);
  }
})

function horizontalComparer(parentRow) {
  return function(a, b) {
      var valA = getCellValue(parentRow, a), valB = getCellValue(parentRow, b)
      return $.isNumeric(valA) && $.isNumeric(valB) ? valA - valB : valA.toString().localeCompare(valB)
  }
}

function getCellValue(row, index){ return $(row).children('td').eq(index).text() }