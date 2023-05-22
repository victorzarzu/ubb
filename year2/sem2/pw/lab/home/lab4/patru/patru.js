const tables = document.querySelectorAll('.sortableTable');
const horizontalTables = document.querySelectorAll('.horizontalTable');

function makeSortable(table) {
    const classes = table.className.split(' ');
    if(classes.includes('horizontalTable')) {
        const headerCells = table.querySelectorAll('tr th:first-child');
        for (let i = 0; i < headerCells.length; i++) {
          headerCells[i].onclick = function () { sortByRow(table, i) };
        }
    } else {
        const headerCells = table.querySelectorAll('tr:first-child th');
        for(let i = 0;i < headerCells.length;i++) {
            headerCells[i].onclick = function() {sortByColumn(table, i, headerCells.length)}
        };
    }
};

function sortByColumn(table, column, noColumns) {
    const values = [];
    for(let j = 0;j < noColumns;j++) {
        const vals = [];
        for(let i = 1;i < table.rows.length;i++) {
            vals.push(table.rows[i].cells[j].innerText);
        }
        values.push(vals);
    }

    const indices = [];
    for(let i = 0;i < noColumns;++i) {
        indices.push(i);
    }
    indices.sort((aIndex, bIndex) => {
        if(!isNaN(Number.parseInt(values[column][aIndex]))) {
            return Number.parseInt(values[column][aIndex]) - Number.parseInt(values[column][bIndex]);
        } else {
            return values[column][aIndex].localeCompare(values[column][bIndex]);
        }
    });
    for(let i = 1;i < table.rows.length;i++) {
        for(let j = 0;j < noColumns;j++) {
            table.rows[i].cells[j].innerText = values[j][indices[i - 1]];
        }
    }
}

function sortByRow(table, row) {
    const values = [];
    for(let i = 0;i < table.rows.length;i++) {
      const vals = [];
      for(let j = 1;j < table.rows[i].cells.length;j++) {
          vals.push(table.rows[i].cells[j].innerText);
      }
      values.push(vals);
    }

    const indices = [];
    for(let i = 0;i < table.rows.length;++i) {
        indices.push(i);
    }

    indices.sort((aIndex, bIndex) => {
      if (!isNaN(Number.parseInt(values[row][aIndex]))) {
        return Number.parseInt(values[row][aIndex]) - Number.parseInt(values[row][bIndex]);
      } else {
        return values[row][aIndex].localeCompare(values[row][bIndex]);
      }
    });

    for(let i = 0;i < table.rows.length;i++) {
      for(let j = 1;j < table.rows[i].cells.length;j++) {
          table.rows[i].cells[j].innerText = values[i][indices[j - 1]];
      }
    }
} 
  
  


function makeHorizontal(table) {
    const content = [];
    const noColumns = Math.max(...Array.from(table.rows).map(row => row.cells.length));
  
    const headerRow = table.rows[0];
    if (headerRow) {
      for (let i = 0; i < headerRow.cells.length; i++) {
        headerRow.cells[i].style.fontWeight = "bold";
      }
    }
  
    for (let i = 0; i < noColumns; i++) {
      const vals = [];
      for (let j = 0; j < table.rows.length; j++) {
        const cell = table.rows[j].cells[i];
        vals.push(cell ? cell.innerHTML : '');
      }
      content.push(vals);
    }
  
    while (table.rows.length > 0) {
      table.deleteRow(0);
    }
  
    for (let i = 0; i < content.length; i++) {
      const newRow = table.insertRow(i);
      for (let j = 0; j < content[i].length; j++) {
        newRow.insertCell(j).innerHTML = content[i][j];
      }
    }
  }
 

/*horizontalTables.forEach(function(table){
    makeHorizontal(table);
});*/

tables.forEach(function(table){
    makeSortable(table);
});