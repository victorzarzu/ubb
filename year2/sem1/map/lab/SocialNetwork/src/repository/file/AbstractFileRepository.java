package repository.file;

import domain.Entity;
import repository.memory.InMemoryRepository;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;

/**
 * Abstract class for a file repository
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private String filename;

    public AbstractFileRepository(String filename) {
        super();
        this.filename = filename;
        loadData();
    }

    /**
     * Method that loads data from file
     */
    private void loadData() {
        try(BufferedReader bufferedReader = new BufferedReader(new FileReader(this.filename))) {
            String line;
            while((line = bufferedReader.readLine()) != null) {
                List<String> atributes = Arrays.asList(line.split(";"));
                E entity = this.extractEntity(atributes);
                super.add(entity);
            }
        }
        catch (FileNotFoundException fileNotFoundException) {
            fileNotFoundException.printStackTrace();
        }
        catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    /**
     * Abstrct method that needs to extract entity from a list of atributes represented as String
     * @param atributes List<String> the atributes of the returned entity
     * @return E
     */
    public abstract E extractEntity(List<String> atributes);

    /**
     * Method that converts the entity to a String
     * @param entity E - the entity to be converted to string
     * @return String - the entity in String format
     */
    protected abstract String entityEntityToString(E entity);
}
